#include "anomaly_manager.h"
#include <algorithm>


AnomalyManager::AnomalyManager()
    : max_active_anomalies(5),
      spawn_chance(0.4f),
      spawn_interval(5.0f) {}
      
AnomalyManager::~AnomalyManager() { despawn_all_anomalies(); }


void AnomalyManager::despawn_anomaly(Anomaly* anomaly) {
    if (!anomaly) return;
    
    auto it = std::find(anomalies.begin(), anomalies.end(), anomaly);
    if (it != anomalies.end()) {
        anomaly->deactivate();
        remove_child(anomaly);
        memdelete(anomaly);
        anomalies.erase(it);
        emit_signal("anomaly_despawned", anomaly);
    }
}

void AnomalyManager::despawn_all_anomalies() {
    for (auto anomaly : anomalies) {
        anomaly->deactivate();
        remove_child(anomaly);
        memdelete(anomaly);
        emit_signal("anomaly_despawned", anomaly);
    }
    anomalies.clear();
}

void AnomalyManager::set_spawn_chance(float chance) {
    spawn_chance = CLAMP(chance, 0.0f, 1.0f);
}

float AnomalyManager::get_spawn_chance() const {
    return spawn_chance;
}
