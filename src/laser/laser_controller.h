#ifndef LASER_CONTROLLER_H
#define LASER_CONTROLLER_H
#include "laser.h"

/** 
 * SUMMARY:
 * This file is a facade & glue for the laser model, and the laser view. 
 * it's responsibility is controlling the interaction between the two.
**/

////////////////////////////////////////////////////////////
///////////Struct///////////////////////////////////////////
///////////////////////////////////////////////////////////

struct LaserController {
    Laser* laser;
};

/////////////////////////////////////////////////////////////
///////////Constructor and Deconstructor/////////////////////
/////////////////////////////////////////////////////////////

LaserController* CreateLaserController(float x, float y, float speed, float lifetime) 
{
    LaserController* controller = (LaserController*)malloc(sizeof(LaserController));
    controller->laser = CreateLaser(x, y, speed, lifetime);
    return controller;
}

void DeconstructLaserController(LaserController* controller) 
{
    DeconstructLaser(controller->laser);
    free(controller);
}

/////////////////////////////////////////////////////////////
///////////Laser_Controller Functions///////////////////////
/////////////////////////////////////////////////////////////

void UpdateLaserController(LaserController* controller, float deltaTime) 
{
}

#endif // LASER_CONTROLLER_H