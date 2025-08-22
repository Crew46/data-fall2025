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

LaserController* CreateLaserController(float x, float y, float speed, float lifetime, Sprite** sprites, int spriteNum) 
{
    LaserController* controller = (LaserController*)malloc(sizeof(LaserController));
    controller->laser = CreateLaser(x, y, speed, lifetime);

    //create and initialize laser view here

    return controller;
}

void DeconstructLaserController(LaserController* controller) 
{
    DeconstructLaser(controller->laser);
    //deconstruct laser view here();
    free(controller);
}

/////////////////////////////////////////////////////////////
///////////Laser_Controller Functions///////////////////////
/////////////////////////////////////////////////////////////

#endif // LASER_CONTROLLER_H