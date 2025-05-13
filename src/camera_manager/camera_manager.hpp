#ifndef CAMERA_MANAGER
#define CAMERA_MANAGER

#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/physics_direct_space_state3d.hpp>
#include <godot_cpp/classes/physics_ray_query_parameters3d.hpp>
#include <godot_cpp/classes/world3d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <vector>
#include "../anomaly/anomaly.hpp"

using namespace godot;

class CameraManager : public Node {
    GDCLASS(CameraManager, Node);
    
private:
    std::vector<Camera3D*> cameras;
    int current_active_camera_id = -1;
    Vector2 mouse_position;
    bool click = false;
    
protected:
    static void _bind_methods() {    
        ClassDB::bind_method(D_METHOD("handle_click"), &CameraManager::handle_click);
    
        ClassDB::bind_method(D_METHOD("get_current_camera_index"), &CameraManager::get_current_camera_index);
        ClassDB::bind_method(D_METHOD("get_camera_count"), &CameraManager::get_camera_count);

        ClassDB::bind_method(D_METHOD("switch_to_camera", "index"), &CameraManager::switch_to_camera);
        ClassDB::bind_method(D_METHOD("switch_to_next_camera"), &CameraManager::switch_to_next_camera);
        ClassDB::bind_method(D_METHOD("switch_to_previous_camera"), &CameraManager::switch_to_previous_camera);
        
        ADD_SIGNAL(MethodInfo("camera_switched", PropertyInfo(Variant::INT, "camera_index")));
        ADD_SIGNAL(MethodInfo("anomaly_hit", PropertyInfo(Variant::OBJECT, "anomaly")));
    }

public:
    void _ready() override;

    void _init() { current_active_camera_id = -1; }

    void _input(const Ref<InputEvent>& event) override;

    void _physics_process(double delta) override;

    void handle_click(const Ref<InputEvent>& event);

    int get_current_camera_index() const { return current_active_camera_id; }
    int get_camera_count() const { return cameras.size(); }

    void switch_to_camera(int index);
    void switch_to_next_camera();
    void switch_to_previous_camera();
};

#endif // CAMERA_MANAGER