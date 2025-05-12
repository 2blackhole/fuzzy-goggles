#include "anomaly.hpp"

void Anomaly::_bind_methods() {
    ClassDB::bind_method(D_METHOD("on_anomaly_deactivated"), &Anomaly::on_anomaly_deactivated);
    ADD_SIGNAL(MethodInfo("deactivated"));

    ClassDB::bind_method(D_METHOD("activate"), &Anomaly::activate);
    ClassDB::bind_method(D_METHOD("deactivate"), &Anomaly::deactivate);
    ClassDB::bind_method(D_METHOD("get_active"), &Anomaly::get_active);
    ClassDB::bind_method(D_METHOD("update_visible_state"), &Anomaly::update_visible_state);
}

void Anomaly::_ready() {
    mesh = get_node<MeshInstance3D>("MeshInstance3D");
    collision_shape = get_node<CollisionShape3D>("CollisionShape3D");

    if (mesh == nullptr) {
        print_line("MeshInstance3D not found!");
        return;
    }
    if (collision_shape == nullptr) {
        print_line("CollisionShape3D not found!");
        return;
    }

    deactivate();
}

void Anomaly::update_visible_state() {
    if (!mesh || !collision_shape) {
        print_error("Attempted to update state with null pointers!");
        return;
    }

    mesh->set_visible(is_active);
    collision_shape->set_disabled(!is_active);
    print_line("Visibility updated: ", is_active ? "Active" : "Inactive");
}

void Anomaly::activate() {
    is_active = true;
    update_visible_state();
}

void Anomaly::deactivate() {
    is_active = false;
    update_visible_state();
}