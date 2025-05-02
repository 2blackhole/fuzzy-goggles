#include "camera_manager.h"

using namespace godot;

void CameraManager::_bind_methods() {
    ClassDB::bind_method(D_METHOD("switch_to_camera", "index"), &CameraManager::switch_to_camera);
    ClassDB::bind_method(D_METHOD("get_current_camera_index"), &CameraManager::get_current_camera_index);
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
        UtilityFunctions::print("Switching to next camera...");
        switch_to_next_camera();
    }
    else if (event->is_action_pressed("ui_left")) {
        UtilityFunctions::print("Switching to previous camera...");
        switch_to_previous_camera();
    }
}

void CameraManager::switch_to_camera(int index) {
    if (index < 0 || index >= cameras.size()) {
        UtilityFunctions::printerr("CameraManager: Invalid camera index!");
        return;
    }
    
    // Деактивируем текущую камеру
    if (current_active_camera_id != -1 && cameras[current_active_camera_id] != nullptr) {
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