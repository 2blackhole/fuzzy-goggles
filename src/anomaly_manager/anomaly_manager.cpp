#include "anomaly_manager.hpp"
#include <algorithm>


void AnomalyManager::_ready() {
    TypedArray vec = get_children();

    for (int i = 0; i < vec.size(); ++i) {
        Anomaly* el = cast_to<Anomaly>(vec[i]);
        if (el) {
            anomalies.push_back(el);
        }
    }
    anomalies_count = anomalies.size();
    print_line("anomalies_count: ", anomalies_count);
    print_line("active_anomalies_count: ", active_anomalies_count);
}