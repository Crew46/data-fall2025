#ifndef LASER_CONTROLLER_MANAGER_H
#define LASER_CONTROLLER_MANAGER_H
#include "../data_structures/doubly_linked_list/doubly_linked_list.h"

/** 
 * SUMMARY:
 * This file keeps tracks of all the instances of laser controller in a linked list
 * also provides functions to do things with those players in the list
**/

//initialize instances list
DoublyLinkedList* laserControllerList = CreateDoublyLinkedList();

/////////////////////////////////////////////////////////////
///////////Laser List Functions//////////////////////////////
/////////////////////////////////////////////////////////////

//update all laser controller in the laser controller list
void UpdateAllLaserControllers()
{
    //loop through all instances of laser controller
    //for(int i = 0; i < instancesOfLaserController; i++)
    //{
        //LaserControllerUpdate();
    //}
}

//deconstruct linked list and all laser controllers in list 
void DeconstructAllLaserControllers()
{
    //loop through all instances of laser controller
    //for(int i = 0; i < instancesOfLaserController; i++)
    //{
        //DeconstructLaserController();    
    //}
}

#endif //LASER_CONTROLLER_MANAGER_H