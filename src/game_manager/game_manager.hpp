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
    double base_spawn_chance = 0.6;
    double current_spawn_chance = 0.4;
    double chance_reduction_factor = 0.4;

    double time_accum = 0;

    int score = 0;

protected:
    static void _bind_methods() {
        ClassDB::bind_method(D_METHOD("set_camera_manager", "manager"), &GameManager::set_camera_manager);
        ClassDB::bind_method(D_METHOD("get_camera_manager"), &GameManager::get_camera_manager);

        ClassDB::bind_method(D_METHOD("set_anomaly_manager", "manager"), &GameManager::set_anomaly_manager);
        ClassDB::bind_method(D_METHOD("get_anomaly_manager"), &GameManager::get_anomaly_manager);

        ClassDB::bind_method(D_METHOD("set_spawn_chance", "chance"), &GameManager::set_base_spawn_chance);
        ClassDB::bind_method(D_METHOD("get_spawn_chance"), &GameManager::get_base_spawn_chance);

        ClassDB::bind_method(D_METHOD("try_spawn_anomaly", "camera_index"), &GameManager::try_spawn_anomaly);
        ClassDB::bind_method(D_METHOD("calculate_dynamic_spawn_chance"), &GameManager::calculate_dynamic_spawn_chance);
        ClassDB::bind_method(D_METHOD("on_anomaly_hit", "anomaly"), &GameManager::on_anomaly_hit);
    }

public:
    void _ready() override;

    void _process(double delta) override;

    void on_anomaly_hit(Anomaly* anomaly);

    void set_camera_manager(CameraManager* manager) { camera_manager = manager; }
    CameraManager* get_camera_manager() const { return camera_manager; }

    void set_anomaly_manager(AnomalyManager* manager) { anomaly_manager = manager; }
    AnomalyManager* get_anomaly_manager() const { return anomaly_manager; }

    void set_base_spawn_chance(double chance) { base_spawn_chance = CLAMP(chance, 0.0f, 1.0f); }
    double get_base_spawn_chance() const { return base_spawn_chance; }

    void try_spawn_anomaly(int camera_index = -1);

    // логарифмическая зависимость кол-ва аномалий
    // и вероятности спавна
    double calculate_dynamic_spawn_chance() const;
};

#endif // GAME_MANAGER