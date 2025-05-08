#ifndef GAME_MANAGER
#define GAME_MANAGER

#include "../anomaly_manager/anomaly_manager.hpp"
#include "../camera_manager/camera_manager.hpp"
#include <godot_cpp/classes/node.hpp>

using namespace godot;

class GameManager : public Node {
    GDCLASS(GameManager, Node);

private:
    AnomalyManager* anomaly_manager = nullptr;
    CameraManager* camera_manager = nullptr;
    float base_spawn_chance = 0.4f;
    float current_spawn_chance = 0.4f;
    float chance_reduction_factor = 0.5f;

  protected:
    static void _bind_methods();

public:
    void _ready() override;

    void set_camera_manager(CameraManager* manager) { camera_manager = manager; }
    CameraManager* get_camera_manager() const { return camera_manager; }

    void set_anomaly_manager(AnomalyManager* manager) { anomaly_manager = manager; }
    AnomalyManager* get_anomaly_manager() const { return anomaly_manager; }

    void set_base_spawn_chance(float chance) { base_spawn_chance = CLAMP(chance, 0.0f, 1.0f); }
    float get_base_spawn_chance() const { return base_spawn_chance; }

    void try_spawn_anomaly_after_camera_switch(int camera_index = -1);

    // логарифмическая зависимость кол-ва аномалий
    // и вероятности спавна
    float calculate_dynamic_spawn_chance() const;

    // void start_game();
    // void end_game();
};

#endif // GAME_MANAGER