#ifndef LASER_CONTROLLER_H
#define LASER_CONTROLLER_H
#include "laser.h"
#include "laser_view.h"
#include "../sprite/sprite.h"

/** 
 * SUMMARY:
 * This file is the glue for the logical interation between the laser model and view 
**/

////////////////////////////////////////////////////////////
///////////Struct///////////////////////////////////////////
///////////////////////////////////////////////////////////

struct LaserController {
    Laser* laser;
    LaserView* laserView;
};

/////////////////////////////////////////////////////////////
///////////Constructor and Deconstructor/////////////////////
/////////////////////////////////////////////////////////////

LaserController* CreateLaserController(Object* object, float speed, float lifetime, Sprite** sprites, int spriteNum) 
{
    LaserController* controller = (LaserController*)malloc(sizeof(LaserController));
    controller->laser = CreateLaser(object, speed, lifetime);

    controller->laserView = CreateLaserView(sprites, spriteNum);

    return controller;
}

void DeconstructLaserController(LaserController* controller) 
{
    DeconstructLaser(controller->laser);
    DeconstructLaserView(controller->laserView);
    free(controller);
}

/////////////////////////////////////////////////////////////
///////////Laser_Controller Functions///////////////////////
/////////////////////////////////////////////////////////////

void LaserControllerUpdate(LaserController* controller)
{
    DrawLaser(controller->laserView, controller->laser);
}

#endif // LASER_CONTROLLER_H