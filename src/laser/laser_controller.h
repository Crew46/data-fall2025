#ifndef LASER_CONTROLLER_H
#define LASER_CONTROLLER_H
#include "laser.h"

struct LaserController {
    Laser* laser;
};

LaserController* CreateLaserController(float x, float y, float speed, float lifetime) 
{
    LaserController* controller = (LaserController*)malloc(sizeof(LaserController));
    controller->laser = CreateLaser(x, y, speed, lifetime);
    return controller;
}

void DeinitializeLaserController(LaserController* controller) 
{
    DeinitializeLaser(controller->laser);
    free(controller);
}

void UpdateLaserController(LaserController* controller, float deltaTime) 
{
}

#endif // LASER_CONTROLLER_H