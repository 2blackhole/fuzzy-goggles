#ifndef GAME_MANAGER
#define GAME_MANAGER

#include "../anomaly_manager/anomaly_manager.hpp"
#include "../camera_manager/camera_manager.hpp"
#include <godot_cpp/classes/node.hpp>

using namespace godot;

class GameManager : public Node {
    GDCLASS(GameManager, Node);

private:
    CameraManager* camera_manager = nullptr;
    AnomalyManager* anomaly_manager = nullptr;

    double base_spawn_chance = 0.6;
    double current_spawn_chance = 0.4;
    double chance_reduction_factor = 0.4;

    double time_accum = 0;

    int max_active_anomalies =7;
    int total_active_anomalies = 0;

    int score = 0;

protected:
    static void _bind_methods() {
        ClassDB::bind_method(D_METHOD("try_spawn_anomaly"), &GameManager::try_spawn_anomaly);
        ClassDB::bind_method(D_METHOD("calculate_dynamic_spawn_chance"), &GameManager::calculate_dynamic_spawn_chance);
        ClassDB::bind_method(D_METHOD("on_anomaly_hit", "anomaly"), &GameManager::on_anomaly_hit);
    }

public:
    void _ready() override;
    void _process(double delta) override;

    int get_score() const { return score; }

    // логарифмическая зависимость кол-ва аномалий
    // и вероятности спавна
    double calculate_dynamic_spawn_chance() const;
    void on_anomaly_hit(Anomaly* anomaly);
    void try_spawn_anomaly();
};

#endif // GAME_MANAGER