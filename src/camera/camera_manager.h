#ifndef CAMERA_MANAGER
#define CAMERA_MANAGER

#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <vector>

using namespace godot;

class CameraManager : public Node {
    GDCLASS(CameraManager, Node);
    
private:
    std::vector<Camera3D*> cameras;
    int current_active_camera_id = -1;
    
  protected:
    static void _bind_methods();
    
public:
    void _ready() override;
    void _input(const Ref<InputEvent>& event) override;
    void _init() { current_active_camera_id = -1; }

    void switch_to_camera(int index);
    // void handle_click(const Ref<InputEvent>& event);
    // void process_raycast(const Vector2& mouse_position);

    int get_current_camera_index() const { return current_active_camera_id; }
    void switch_to_next_camera();
    void switch_to_previous_camera();
};

#endif // CAMERA_MANAGER