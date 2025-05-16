#include "camera.hpp"

AnomalyManager* CameraP::get_anomaly_manager() const { return anomaly_manager; }

void CameraP::_ready() {
    TypedArray vec = get_children();
    anomaly_manager = Object::cast_to<AnomalyManager>(get_node_or_null("AnomalyManager"));
    if (!anomaly_manager) {
        print_line("ALARAM!!! ANOMALY MANAGER ISNTLODED PAREN");
        return;
    }
}