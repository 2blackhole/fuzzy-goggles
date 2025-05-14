#ifndef CAMERA
#define CAMERA

#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include "anomaly_manager/anomaly_manager.hpp"

using namespace godot;

class CameraP : public Camera3D {
    GDCLASS(CameraP, Camera3D);

private:
    AnomalyManager* anomaly_manager = nullptr;

protected:
    static void _bind_methods() {    
        ClassDB::bind_method(D_METHOD("get_anomaly_manager"), &CameraP::get_anomaly_manager);
    }
public:
    void _ready() override;
    AnomalyManager* get_anomaly_manager();
};


#endif