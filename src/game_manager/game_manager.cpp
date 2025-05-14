#include "game_manager.hpp"
#include <godot_cpp/classes/engine.hpp>
#include <random>


void GameManager::_ready() {
    if (Engine::get_singleton()->is_editor_hint()) {
        return;
    }
    if (camera_manager == nullptr) {
        camera_manager = Object::cast_to<CameraManager>(get_node_or_null("CameraManager"));
    }
    if (camera_manager != nullptr) {
        camera_manager->connect("camera_switched", Callable(this, "try_spawn_anomaly_after_camera_switch"));
        camera_manager->connect("anomaly_hit", Callable(this, "on_anomaly_hit"));
    }
}

void GameManager::_process(double delta) {
    time_accum += delta;
    if (time_accum >= 1.0) {
        if (camera_manager) {
            int current_cam_index = camera_manager->get_current_camera_index();
            static std::random_device rd;
            static std::mt19937 gen(rd());
            std::uniform_int_distribution<int> chance_dist(0, camera_manager->get_camera_count() - 2);
            int rand_anomaly_manager = chance_dist(gen);
            if (rand_anomaly_manager >= current_cam_index) ++rand_anomaly_manager;
            anomaly_manager = (*camera_manager)[rand_anomaly_manager]->get_anomaly_manager();
            try_spawn_anomaly();

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

void GameManager::try_spawn_anomaly() {
    if (!anomaly_manager || !camera_manager) {
        return;
    }

    if (total_active_anomalies >= max_active_anomalies) {
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

    int tmp_count = 0;
    for (int i = 0; i < camera_manager->get_camera_count(); i++) {
        tmp_count += (*camera_manager)[i]->get_anomaly_manager()->get_active_anomalies_count();
    }
    total_active_anomalies = tmp_count;
    print_line_rich("\nTOTAL ACTIVE ANOMALIES : ", total_active_anomalies, "\n");
}

double GameManager::calculate_dynamic_spawn_chance() const {
    if (total_active_anomalies <= 0) {
        print_line("active anom <= 0");
        return base_spawn_chance;
    }

    if (max_active_anomalies <= 0) {
        print_line("max act <= 0");
        return base_spawn_chance;
    }

    if (total_active_anomalies >= max_active_anomalies) {
        print_line("act >= max act");
        return 0.0;
    }

    double log_factor = log2(1 + total_active_anomalies);
    return base_spawn_chance * pow(1 - chance_reduction_factor, log_factor);
}