#include "camera_manager.hpp"

using namespace godot;

void CameraManager::_bind_methods() {    
    ClassDB::bind_method(D_METHOD("handle_click"), &CameraManager::handle_click);

    ClassDB::bind_method(D_METHOD("get_current_camera_index"), &CameraManager::get_current_camera_index);

    ClassDB::bind_method(D_METHOD("switch_to_camera", "index"), &CameraManager::switch_to_camera);
    ClassDB::bind_method(D_METHOD("switch_to_next_camera"), &CameraManager::switch_to_next_camera);
    ClassDB::bind_method(D_METHOD("switch_to_previous_camera"), &CameraManager::switch_to_previous_camera);
    
    ADD_SIGNAL(MethodInfo("camera_switched", PropertyInfo(Variant::INT, "camera_index")));
    ADD_SIGNAL(MethodInfo("anomaly_clicked", PropertyInfo(Variant::OBJECT, "anomaly")));
}

void CameraManager::_ready() {
    cameras.clear();

    TypedArray<Node> children = get_children();

    for (int i = 0; i < children.size(); ++i) {
        if (Camera3D* camera = Object::cast_to<Camera3D>(children[i])) {
            cameras.push_back(camera);
            UtilityFunctions::print("Registered camera: ",camera->get_name());
        }
    }

    if (cameras.empty()) { return; }

    switch_to_camera(0);
}


void CameraManager::_input(const Ref<InputEvent>& event) {
    if (event.is_null()) { return; }

    UtilityFunctions::print("Input event detected: ", event->as_text()); // вообще все инпуты показывает

    if (event->is_action_pressed("ui_right")) {
        print_line("Switching to next camera...");
        switch_to_next_camera();
    } else if (event->is_action_pressed("ui_left")) {
        print_line("Switching to previous camera...");
        switch_to_previous_camera();
    } else {
        handle_click(event);
    }
}

void CameraManager::_physics_process(double delta) {
    Camera3D* current_cam = cameras[current_active_camera_id];
    if (!current_cam) {
        print_line("Penis");
        return;
    }

    World3D* world = current_cam->get_world_3d().ptr();
    if (!world) {
        print_error("Failed to get World3D");
        return;
    }

    PhysicsDirectSpaceState3D* space_state = world->get_direct_space_state();
    if (!space_state) {
        print_error("Failed to get SpaceState");
        return;
    }

    if (click) {
        Vector3 from = current_cam->project_ray_origin(mouse_position);
        Vector3 to = from + current_cam->project_ray_normal(mouse_position)*1000.0f;
        Ref<PhysicsRayQueryParameters3D> params = PhysicsRayQueryParameters3D::create(from, to);

        params->set_collide_with_areas(true);
        params->set_collide_with_bodies(true);

        Dictionary ray_result = space_state->intersect_ray(params);
        click = false;
        print_line(ray_result);
        if (ray_result.has("collider")) {
            Object* collider = ray_result["collider"];
            if (collider) {
                
                Node* collider_node = Object::cast_to<Node>(collider);
                if (collider_node) {
                    UtilityFunctions::print("Hit node: ", collider_node->get_name());
                    
                    Anomaly* anomaly = Object::cast_to<Anomaly>(collider_node);
                    if (!anomaly) {
                        anomaly = Object::cast_to<Anomaly>(collider_node->get_parent());
                    }
                    
                    if (anomaly) {
                        UtilityFunctions::print("Hit anomaly: ", anomaly->get_name());
                        anomaly->deactivate();
                        emit_signal("raycast_hit", anomaly);
                    }
                }
            }
        } else {
            UtilityFunctions::print("Raycast didn't hit anything");
        }
    }
}

void CameraManager::handle_click(const Ref<InputEvent>& event) {
    if (event.is_null() || current_active_camera_id == -1) {
        return;
    }

    Ref<InputEventMouseButton> mouse_event = event;
    if (mouse_event.is_valid()
            && mouse_event->get_button_index() == MOUSE_BUTTON_LEFT
            && mouse_event->is_pressed()) {
                mouse_position = mouse_event->get_position();
                click = true;
            }
}

void CameraManager::switch_to_camera(int index) {
    if (index < 0 || index >= cameras.size()) {
        UtilityFunctions::printerr("CameraManager: Invalid camera index!");
        return;
    }

    // Деактивируем текущую камеру
    if (current_active_camera_id != -1 &&
        cameras[current_active_camera_id] != nullptr) {
        cameras[current_active_camera_id]->set_current(false);
    }

    // Активируем новую
    current_active_camera_id = index;
    cameras[index]->set_current(true);

    emit_signal("camera_switched", index);
}

void CameraManager::switch_to_next_camera() {
    if (cameras.empty()) return;
    switch_to_camera((current_active_camera_id + 1) % cameras.size());
}

void CameraManager::switch_to_previous_camera() {
    if (cameras.empty()) return;
    switch_to_camera((current_active_camera_id - 1) % cameras.size());
}