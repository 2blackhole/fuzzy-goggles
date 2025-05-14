#ifndef ANOMALY_MANAGER
#define ANOMALY_MANAGER

#include <godot_cpp/classes/node.hpp>
#include "anomaly.hpp"

using namespace godot;

class AnomalyManager : public Node {
    GDCLASS(AnomalyManager, Node);

private:
    std::vector<Anomaly*> anomalies;
    int anomalies_count = 0;
    int active_anomalies_count = 0;
    //int max_active_anomalies = 5;

protected:
    static void _bind_methods() {
        ClassDB::bind_method(D_METHOD("set_anomalies_count", "count"), &AnomalyManager::set_anomalies_count);
        ClassDB::bind_method(D_METHOD("get_anomalies_count"), &AnomalyManager::get_anomalies_count);
    
        // ClassDB::bind_method(D_METHOD("set_max_active_anomalies", "max"), &AnomalyManager::set_max_active_anomalies);
        // ClassDB::bind_method(D_METHOD("get_max_active_anomalies"), &AnomalyManager::get_max_active_anomalies);
    
        ClassDB::bind_method(D_METHOD("set_active_anomalies_count", "count"), &AnomalyManager::set_active_anomalies_count);
        ClassDB::bind_method(D_METHOD("get_active_anomalies_count"), &AnomalyManager::get_active_anomalies_count);
    
        ClassDB::bind_method(D_METHOD("on_anomaly_deactivated"), &AnomalyManager::on_anomaly_deactivated);
    }

public:
    void _ready() override;

    void _init() {
        anomalies_count = 0;
        active_anomalies_count = 0;
        //max_active_anomalies = 5;
    }

    int get_anomalies_count() const { return anomalies_count; }
    void set_anomalies_count(int i) { anomalies_count = i; }

    // int get_max_active_anomalies() const  { return max_active_anomalies; }
    // void set_max_active_anomalies(int i) { max_active_anomalies = i; }

    int get_active_anomalies_count() const { return active_anomalies_count; }
    void set_active_anomalies_count(int i) { active_anomalies_count = i; }

    Anomaly* operator()(int i) { return anomalies[i]; }

    void on_anomaly_deactivated();
};

#endif // ANOMALY_MANAGER