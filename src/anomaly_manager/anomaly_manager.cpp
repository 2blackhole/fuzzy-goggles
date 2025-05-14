#include "anomaly_manager.hpp"
#include <algorithm>


void AnomalyManager::_ready() {
    TypedArray vec = get_children();

    for (int i = 0; i < vec.size(); ++i) {
        Anomaly* el = cast_to<Anomaly>(vec[i]);
        if (el) {
            anomalies.push_back(el);
            el->connect("deactivated", Callable(this, "on_anomaly_deactivated"));
        }
    }
    anomalies_count = anomalies.size();
    print_line("anomalies_count: ", anomalies_count);
    print_line("active_anomalies_count: ", active_anomalies_count);
    // print_line("max_active_anomalies: ", max_active_anomalies);
}

void AnomalyManager::on_anomaly_deactivated() {
    // active_anomalies_count = MAX(0, active_anomalies_count - 1);
    print_line("Anomaly deactivated. Active count: ", active_anomalies_count);
}