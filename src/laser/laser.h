#ifndef LASER_H
#define LASER_H
#include "misc.h"
#include "video.h"
#include "../vector/vector2.h"
#include "../object.h"
#include "../data_structures/doubly_linked_list/doubly_linked_list.h"

/** 
 * SUMMARY:
 * This is the model of the laser: the fundamental properties and behaviors.
 * This file defines the laser struct and its associated functions.
**/

//=========================================================
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////PART 1: MODEL///////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

/////////////////////////////////////////////////
///////////Struct////////////////////////////////
/////////////////////////////////////////////////

struct Laser {
    Object* object;
    float speed; // Speed of the laser in pixels per second
    float lifetime; // Lifetime of the laser in seconds
};

/////////////////////////////////////////////////
///////////Constructor and Deconstructor/////////
/////////////////////////////////////////////////

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

//=========================================================
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////PART 2: VISUAL FUNCTIONS////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void DrawLaser()
{

}

//=========================================================
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////PART 3: LOGICAL CONNECTION//////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void LaserControllerUpdate(LaserController* controller)
{
    DrawLaser(controller->laserView, controller->laser);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////PART 4: INSTANCES MANAGEMENT////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

//initialize instances list
DoublyLinkedList* laserControllerList = CreateDoublyLinkedList();

//update all laser controller in the laser controller list
void UpdateAllLasers()
{
    //loop through all instances of laser controller
    //for(int i = 0; i < instancesOfLaserController; i++)
    //{
        //LaserControllerUpdate();
    //}
}

//deconstruct linked list and all laser controllers in list 
void DeconstructAllLasers()
{
    //loop through all instances of laser controller
    //for(int i = 0; i < instancesOfLaserController; i++)
    //{
        //DeconstructLaserController();    
    //}
}

#endif // LASER_H