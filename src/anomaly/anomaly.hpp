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

    static int id;

protected:
    static void _bind_methods();

public:
    void _ready() override;

    void _init() {
        collision_shape = nullptr;
        mesh = nullptr;
        is_active = false;
    }

    void on_anomaly_deactivated() { emit_signal("deactivated"); }

    bool get_active() const { return is_active; }

    void activate();
    void deactivate();

    void update_visible_state();
};

#endif // ANOMALY