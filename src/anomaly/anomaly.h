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
    String type;
    bool is_active = false;
    
protected:
    static void _bind_methods();
    
public:
    // ~Anomaly() {
    //     memdelete(collision_shape);
    //     memdelete(mesh);
    // }
    // Anomaly() = default;
    void _ready() override;
    void _init() {}
    static int id;
    
    void set_type(const String& _type) {
        type = _type;
    }

    String get_type() const {
        return type;
    }

    bool get_active() const {
        return is_active;
    }

    void activate();
    void deactivate();

    void update_visible_state();
};
#endif