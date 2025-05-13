#include "game_manager.hpp"
#include <godot_cpp/classes/engine.hpp>
#include <random>


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
        camera_manager->connect("anomaly_hit", Callable(this, "on_anomaly_hit"));
    }
}

void GameManager::_process(double delta) {
    time_accum += delta;
    if (time_accum >= 1.0) {
        print_line("otladka");
        if (camera_manager) {
            int current_cam_index = camera_manager->get_current_camera_index();
            try_spawn_anomaly(current_cam_index);
        }
        time_accum = 0.0;
    }
}

void GameManager::on_anomaly_hit(Anomaly* anomaly) {
    if (!anomaly || !anomaly_manager) return;

    if (anomaly->get_active()) {
        anomaly->deactivate();
        int asd = anomaly_manager->get_active_anomalies_count();
        anomaly_manager->set_active_anomalies_count(asd - 1);
        ++score;
        print_line("Score: ", score);
    }
}

void GameManager::try_spawn_anomaly(int camera_index) {
    if (!anomaly_manager || !camera_manager) {
        return;
    }

    if (anomaly_manager->get_active_anomalies_count() >= anomaly_manager->get_max_active_anomalies()) {
        print_line("Max active anomalies reached");
        return;
    }

    current_spawn_chance = calculate_dynamic_spawn_chance();
    print_line("Current spawn chance:", current_spawn_chance);

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<double> chance_dist(0.0, 1.0);


    if (chance_dist(gen) < current_spawn_chance) {
        int total_anomalies = anomaly_manager->get_anomalies_count();
        if (total_anomalies > 0) {
            std::uniform_int_distribution<int> index_dist(0, total_anomalies - 1);
            int anomaly_index = index_dist(gen);
            Anomaly* anomaly = (*anomaly_manager)(anomaly_index);
            
            if (anomaly && !anomaly->get_active()) {
                anomaly->activate();
                anomaly_manager->set_active_anomalies_count(anomaly_manager->get_active_anomalies_count() + 1);
                print_line("Anomaly activated", anomaly->get_name());
            }
        }
    }
}

double GameManager::calculate_dynamic_spawn_chance() const {
    if (!anomaly_manager) return base_spawn_chance;

    int active = anomaly_manager->get_active_anomalies_count();
    int max_active = anomaly_manager->get_max_active_anomalies();

    if (active <= 0) {
        print_line("active anom <= 0");
        return base_spawn_chance;
    }

    if (max_active <= 0) {
        print_line("max act <= 0");
        return base_spawn_chance;
    }

    if (active >= max_active) {
        print_line("act >= max act");
        return 0.0;
    }

    double log_factor = log2(1 + active);
    return base_spawn_chance * pow(1 - chance_reduction_factor, log_factor);
}