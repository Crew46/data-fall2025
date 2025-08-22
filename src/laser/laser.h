#ifndef LASER_H
#define LASER_H
#include "misc.h"
#include "../vector/vector2.h"
#include "../data_structures/linkedlist.h"

/** 
 * SUMMARY:
 * This is the model of the laser: the fundamental properties and behaviors.
 * This file defines the laser struct and its associated functions.
**/

////////////////////////////////////////////////////////////
///////////Struct///////////////////////////////////////////
///////////////////////////////////////////////////////////

struct Laser {
    Vector2* position; // Position of the laser
    float speed; // Speed of the laser in pixels per second
    float lifetime; // Lifetime of the laser in seconds
};

///////////////////////////////////////////////////////////
///////////Constructor and Deconstructor///////////////////
///////////////////////////////////////////////////////////

Laser* CreateLaser(float x, float y, float speed, float lifetime)
{
    Laser* laser = (Laser*)malloc(sizeof(Laser));
    laser->position = CreateVector2(x, y);
    laser->speed = speed;
    laser->lifetime = lifetime;
    return laser;
}

void DeconstructLaser(Laser* laser)
{
    free(laser->position);
    free(laser);
}

///////////////////////////////////////////////////////////
///////////Laser Functions/////////////////////////////////
///////////////////////////////////////////////////////////

#endif // LASER_H