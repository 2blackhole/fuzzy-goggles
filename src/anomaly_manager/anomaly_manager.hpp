#ifndef ANOMALY_MANAGER
#define ANOMALY_MANAGER

#include <godot_cpp/classes/node.hpp>
#include "anomaly.hpp"

using namespace godot;

class AnomalyManager : public Node {
    GDCLASS(AnomalyManager, Node);

private:
    std::vector<Anomaly*> anomalies;
    int active_anomalies_count = 0;
    int anomalies_count = 0;
    int max_active_anomalies = 5;

  protected:
    static void _bind_methods();

public:
    void _ready() override;
    
    void _init() {
        max_active_anomalies = 5;
        active_anomalies_count = 0;
        anomalies_count = 0;
    }

    int get_anomalies_count() const { return anomalies_count; }
    void set_anomalies_count(int i) { anomalies_count = i; }

    int get_max_active_anomalies() const  { return max_active_anomalies; }
    void set_max_active_anomalies(int i) { max_active_anomalies = i; }

    int get_active_anomalies_count() const { return active_anomalies_count; }
    void set_active_anomalies_count(int i) { active_anomalies_count = i; }

    Anomaly* operator()(int i) { return anomalies[i]; }

    void on_anomaly_deactivated();
    void superpuperbingcheling_yehaopien_bingchelin(
        int SUPADUPA____CHINLGSDL_SURNAKAFLAFD);
};

#endif // ANOMALY_MANAGER