#ifndef LASER_CONTROLLER_MANAGER_H
#define LASER_CONTROLLER_MANAGER_H
#include "../data_structures/linkedlist.h"

/** 
 * SUMMARY:
 * This file keeps tracks of all the instances of laser controller in a linked list
 * also provides functions to do things with those players in the list
**/

//initialize instances list
DoublyNode* laserControllerList = CreateDoublyNode();
int instancesOfLaserController = 0;

//update all laser controller in the laser controller list
void UpdateAllLaserControllers(float deltaTime)
{
    //loop through all instances of laser controller
    for(int i = 0; i < instancesOfLaserController; i++)
    {
        //LaserControllerUpdate();
    }
}

void DeconstructAllLaserControllers()
{
    //loop through all instances of laser controller
    for(int i = 0; i < instancesOfLaserController; i++)
    {
        //DeconstructLaserController();    
    }
}

#endif //LASER_CONTROLLER_MANAGER_H