#include "game_manager.hpp"
#include <godot_cpp/classes/engine.hpp>
#include <random>

void GameManager::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_camera_manager", "manager"), &GameManager::set_camera_manager);
    ClassDB::bind_method(D_METHOD("get_camera_manager"), &GameManager::get_camera_manager);

    ClassDB::bind_method(D_METHOD("set_anomaly_manager", "manager"), &GameManager::set_anomaly_manager);
    ClassDB::bind_method(D_METHOD("get_anomaly_manager"), &GameManager::get_anomaly_manager);

    ClassDB::bind_method(D_METHOD("set_spawn_chance", "chance"), &GameManager::set_spawn_chance);
    ClassDB::bind_method(D_METHOD("get_spawn_chance"), &GameManager::get_spawn_chance);

    ClassDB::bind_method(D_METHOD("try_spawn_anomaly_after_camera_switch", "camera_index"), &GameManager::try_spawn_anomaly_after_camera_switch);
}

void GameManager::_ready() {
    // чтобы не искало ноды пока в эдиторе -> живем без крашей
    if (Engine::get_singleton()->is_editor_hint()) {
        return;
    }

    if (camera_manager == nullptr) {
        camera_manager = Object::cast_to<CameraManager>(get_node_or_null("CameraManager"));
    }

    if (anomaly_manager == nullptr) {
        anomaly_manager = Object::cast_to<AnomalyManager>(get_node_or_null("AnomalyManager"));
    }

    if (camera_manager != nullptr) {
        camera_manager->connect("camera_switched", Callable(this, "try_spawn_anomaly_after_camera_switch"));
    }
}

void GameManager::try_spawn_anomaly_after_camera_switch(int camera_index) {
    if (!anomaly_manager || !camera_manager || !camera_index) {
        print_line("govno");
        return;
    }

    if (anomaly_manager->get_active_anomalies_count() >= anomaly_manager->get_max_active_anomalies()) {
        print_line("peniks");
        return;
    }

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> chance_dist(0.0f, 1.0f);

    if (chance_dist(gen) < spawn_chance) {
        int total_anomalies = anomaly_manager->get_anomalies_count();
        if (total_anomalies > 0) {
            std::uniform_int_distribution<int> index_dist(0, total_anomalies - 1);
            int anomaly_index = index_dist(gen);

            Anomaly* anomaly = (*anomaly_manager)(anomaly_index);
            if (anomaly && !anomaly->get_active()) {
                anomaly->activate();
                anomaly_manager->set_active_anomalies_count(anomaly_manager->get_active_anomalies_count() + 1);
                print_line("Anomaly activated: ", anomaly->get_name());
            }
        }
    }
}