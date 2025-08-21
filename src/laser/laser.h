#ifndef LASER_H
#define LASER_H
#include "misc.h"
#include "../vector/vector2.h"

/** 
 * SUMMARY:
 * This is the model of the player: the fundamental properties and behaviors of the player.
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

void UpdateLaser(Laser* laser, float deltaTime)
{
    // Move the laser based on its speed and the delta time
    Vector2* movement = CreateVector2(laser->speed * deltaTime, 0);
    AddVector2Components(laser->position, movement, laser->position);
    free(movement);

    // Decrease the lifetime of the laser
    laser->lifetime -= deltaTime;
}

#endif // LASER_H