#include "anomaly.hpp"

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