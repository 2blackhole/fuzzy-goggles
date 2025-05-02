#include "camera_manager.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void CameraManager::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_input", "event"), &CameraManager::_input);
    ClassDB::bind_method(D_METHOD("register_camera", "camera"), &CameraManager::register_camera);
    ClassDB::bind_method(D_METHOD("switch_to_camera", "index"), &CameraManager::switch_to_camera);
    ClassDB::bind_method(D_METHOD("get_current_camera_index"), &CameraManager::get_current_camera_index);
    ClassDB::bind_method(D_METHOD("switch_to_next_camera"), &CameraManager::switch_to_next_camera);
    ClassDB::bind_method(D_METHOD("switch_to_previous_camera"), &CameraManager::switch_to_previous_camera);

    ADD_SIGNAL(MethodInfo("camera_switched", PropertyInfo(Variant::INT, "camera_index")));
    ADD_SIGNAL(MethodInfo("anomaly_clicked", PropertyInfo(Variant::OBJECT, "anomaly")));
}

void CameraManager::_ready() {
    Node* parent = get_parent();
    if (!parent) { return; }

    TypedArray<Node> children = parent->get_children();

    cameras.clear();

    for (int i = 0; i < children.size(); ++i) {
        if (Camera3D* camera = Object::cast_to<Camera3D>(children[i])) { cameras.push_back(camera); }
    }

    if (cameras.empty()) {
        print_error("No cameras found in scene!");
        return;
    }

    for (Camera3D* camera : cameras) {
        register_camera(camera);
    }

    print_line("Camera system initialized. Total cameras: ", cameras.size());
}

void CameraManager::_input(const Ref<InputEvent>& event) {
    if (event->is_action_pressed("ui_right")) {
        switch_to_next_camera();
    } else if (event->is_action_pressed("ui_left")) {
        switch_to_previous_camera();
    }
}

void CameraManager::register_camera(Camera3D* camera) {
    if (!camera) return;
    cameras.push_back(camera);

    if (current_active_camera_id == -1) {
        switch_to_camera(0);
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