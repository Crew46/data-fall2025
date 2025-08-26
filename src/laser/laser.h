#ifndef LASER_H
#define LASER_H
#include "misc.h"
#include "../vector/vector2.h"

/** 
 * SUMMARY:
 * This is the model of the laser: the fundamental properties and behaviors.
 * This file defines the laser struct and its associated functions.
**/

////////////////////////////////////////////////////////////
///////////Struct///////////////////////////////////////////
///////////////////////////////////////////////////////////

struct Laser {
    Object* object;
    float speed; // Speed of the laser in pixels per second
    float lifetime; // Lifetime of the laser in seconds
};

///////////////////////////////////////////////////////////
///////////Constructor and Deconstructor///////////////////
///////////////////////////////////////////////////////////

Laser* CreateLaser(Object* object, float speed, float lifetime)
{
    Laser* laser = (Laser*)malloc(sizeof(Laser));
    laser->object = object;
    laser->speed = speed;
    laser->lifetime = lifetime;
    return laser;
}

void DeconstructLaser(Laser* laser)
{
    free(laser);
}

///////////////////////////////////////////////////////////
///////////Laser Functions/////////////////////////////////
///////////////////////////////////////////////////////////

#endif // LASER_H