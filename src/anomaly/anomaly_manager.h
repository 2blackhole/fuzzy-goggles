#ifndef ANOMALY_MANAGER
#define ANOMALY_MANAGER

#include <godot_cpp/classes/node.hpp>
#include "anomaly.h"

using namespace godot;

class AnomalyManager : public Node {
    GDCLASS(AnomalyManager, Node);

private:
    std::vector<Anomaly*> anomalies;
    int anomaly_count;
    int max_active_anomalies;
    float spawn_chance;
    float spawn_interval;

protected:
    static void _bind_methods();
    
public:
    AnomalyManager();
    ~AnomalyManager();

    void despawn_anomaly(Anomaly* anomaly);
    void despawn_all_anomalies();
    
    void set_spawn_chance(float chance);
    float get_spawn_chance() const;

};
#endif