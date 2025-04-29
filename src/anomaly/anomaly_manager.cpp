#include "anomaly_manager.h"
#include <algorithm>

void AnomalyManager::_bind_methods() {
    // Регистрация свойств
    ClassDB::bind_method(D_METHOD("set_anomalies_count", "count"), &AnomalyManager::set_anomalies_count);
    ClassDB::bind_method(D_METHOD("get_anomalies_count"), &AnomalyManager::get_anomalies_count);
    ClassDB::add_property("AnomalyManager", PropertyInfo(Variant::INT, "anomalies_count"), "set_anomalies_count", "get_anomalies_count");

    ClassDB::bind_method(D_METHOD("set_max_active_anomalies", "max"), &AnomalyManager::set_max_active_anomalies);
    ClassDB::bind_method(D_METHOD("get_max_active_anomalies"), &AnomalyManager::get_max_active_anomalies);
    ClassDB::add_property("AnomalyManager", PropertyInfo(Variant::INT, "max_active_anomalies"), "set_max_active_anomalies", "get_max_active_anomalies");

    ClassDB::bind_method(D_METHOD("set_active_anomalies_count", "count"), &AnomalyManager::set_active_anomalies_count);
    ClassDB::bind_method(D_METHOD("get_active_anomalies_count"), &AnomalyManager::get_active_anomalies_count);
    ClassDB::add_property("AnomalyManager", PropertyInfo(Variant::INT, "active_anomalies_count"), "set_active_anomalies_count", "get_active_anomalies_count");

    ClassDB::bind_method(D_METHOD("set_spawn_chance", "chance"), &AnomalyManager::set_spawn_chance);
    ClassDB::bind_method(D_METHOD("get_spawn_chance"), &AnomalyManager::get_spawn_chance);
    ClassDB::add_property("AnomalyManager", PropertyInfo(Variant::FLOAT, "spawn_chance"), "set_spawn_chance", "get_spawn_chance");

    // Регистрация специального метода
    ClassDB::bind_method(D_METHOD("superpuperbingcheling_yehaopien_bingchelin", "value"), &AnomalyManager::superpuperbingcheling_yehaopien_bingchelin);
}

void AnomalyManager::_ready() {
    TypedArray vec = get_children(); 
    for (int i = 0; i < vec.size(); i++) {
        Anomaly* el = cast_to<Anomaly> (vec[i]);
        if (el) {
            anomalies.push_back(el);
            anomalies_count++;
            print_line("Anomaly added: ", "total : ", get_anomalies_count());
            print_line(el->get_name());
        }
    }
}

void AnomalyManager::superpuperbingcheling_yehaopien_bingchelin(int SUPADUPA____CHINLGSDL_SURNAKAFLAFD) {
    for (int i = 0; i < get_anomalies_count(); i++) {
        anomalies[i]->activate();
        active_anomalies_count++;
    }
}
