#ifndef ANOMALY_MANAGER
#define ANOMALY_MANAGER

#include <godot_cpp/classes/node.hpp>
#include "anomaly.h"

using namespace godot;

class AnomalyManager : public Node {
    GDCLASS(AnomalyManager, Node);

private:
    std::vector<Anomaly*> anomalies;
    int active_anomalies_count = 0;
    int anomalies_count = 0;
    int max_active_anomalies = 5;
    float spawn_chance = 0.4f;
    float spawn_interval = 5.0f;
    
protected:
    static void _bind_methods();
    
public:
    void _ready() override;
    void _init() {
        max_active_anomalies = 5;
        active_anomalies_count = 0;
        anomalies_count = 0;
        spawn_chance = 0.4f;
        spawn_interval = 5.0f;
    }

    void set_anomalies_count(int i) {
        anomalies_count = i;
    }
    
    int get_anomalies_count() {
        return anomalies_count;
    }

    int get_max_active_anomalies() {
        return max_active_anomalies;
    }

    void set_max_active_anomalies(int i) {
        max_active_anomalies = i;
    }

    int get_active_anomalies_count() {
        return active_anomalies_count;
    }

    void set_active_anomalies_count(int i) {
        active_anomalies_count = i;
    }

    Anomaly* operator() (int i) {
        return anomalies[i];
    }
    
    void set_spawn_chance(float chance) {
        spawn_chance = CLAMP(chance, 0.0f, 1.0f);
    }

    float get_spawn_chance() const {
        return spawn_chance;
    }

    void superpuperbingcheling_yehaopien_bingchelin(int SUPADUPA____CHINLGSDL_SURNAKAFLAFD);
};

#endif // ANOMALY_MANAGER