#ifndef CAMERA_MANAGER
#define CAMERA_MANAGER

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <vector>

namespace godot {

class CameraManager : public Node {
    GDCLASS(CameraManager, Node);
    
private:
    std::vector<Camera3D*> cameras;
    int current_active_camera_id = -1;
    double click_cooldown = 0.5;
    double last_click_time = 0.0;
    
protected:
    static void _bind_methods();
    
public:
    CameraManager() = default;
    ~CameraManager();

    void _process(double delta) override;
    void register_camera(Camera3D* camera);
    void switch_to_camera(int index);
    // void handle_click(const Ref<InputEvent>& event);
    // void process_raycast(const Vector2& mouse_position);
    
    int get_current_camera_index() const { return current_active_camera_id; }
    void switch_to_next_camera();
    void switch_to_previous_camera();
};

} // namespace godot

#endif // CAMERA_MANAGER