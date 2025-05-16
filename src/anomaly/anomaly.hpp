#ifndef ANOMALY
#define ANOMALY

#include <godot_cpp/classes/area3d.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/collision_shape3d.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>

using namespace godot;

class Anomaly : public Area3D {
    GDCLASS(Anomaly, Area3D);
    
private:
    CollisionShape3D* collision_shape = nullptr;
    MeshInstance3D* mesh = nullptr;
    bool is_active = false;
    bool was_called = false;

protected:
    static void _bind_methods() {
        ClassDB::bind_method(D_METHOD("activate"), &Anomaly::activate);
        ClassDB::bind_method(D_METHOD("deactivate"), &Anomaly::deactivate);
        ClassDB::bind_method(D_METHOD("get_active"), &Anomaly::get_active);
        ClassDB::bind_method(D_METHOD("set_called", "call"), &Anomaly::set_called);
        ClassDB::bind_method(D_METHOD("get_called"), &Anomaly::get_called);
        ClassDB::bind_method(D_METHOD("update_visible_state"), &Anomaly::update_visible_state);
    }

public:
    void _ready() override;

    bool get_active() const { return is_active; }

    void set_called(bool call) { was_called = call; }
    bool get_called() const { return was_called; }

    void activate();
    void deactivate();

    void update_visible_state();
};

#endif // ANOMALY