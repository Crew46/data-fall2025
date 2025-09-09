#ifndef LASER_H
#define LASER_H
#include "misc.h"
#include "video.h"
#include "../vector/vector2.h"
#include "../object.h"
#include "../data_structures/doubly_linked_list/doubly_linked_list.h"

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 1: MODEL///////////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

/////////////////////////////////////////////////
///////////1: Struct/////////////////////////////
/////////////////////////////////////////////////

enum LaserType
{
    LASER_TYPE_LASER_CANNON,
    LASER_TYPE_MISSILE_LAUNCHER,
    LASER_TYPE_LIGHTNING_ROD,
};

struct Laser {
    Object object;
    LaserType type;
    float lifetime; // Lifetime of the laser in seconds
    float age;
};


/////////////////////////////////////////////////
///////////1: Constructor and Deconstructor//////
/////////////////////////////////////////////////

Laser* CreateLaser(int* name, int textureID, int regionID, int id, int x, int y, bool isActive, int speed, LaserType type, float lifetime)
{
    Laser* laser = (Laser*)malloc(sizeof(Laser));
    InitializeObject(&laser->object, name, textureID, regionID, id, x, y, isActive, speed);
    laser->type = type;
    laser->lifetime = lifetime;
    return laser;
}

void DeconstructLaser(Laser* laser)
{
    free(laser);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 2: VISUAL FUNCTIONS////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void DrawLaser(Laser* laser)
{
    DrawObject(&laser->object);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 3: LOGICAL CONNECTION//////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void LaserUpdate(Laser* laser)
{
    //logical operations here

    //draw
    DrawLaser(laser);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 4: INSTANCES MANAGEMENT////////////////////
///////////////////////////////////////////////////////////
//=========================================================

//initialize instances list
DoublyLinkedList* lasersList = CreateDoublyLinkedList();

//update all laser controller in the laser controller list
void UpdateAllLasers()
{
    //loop through all instances of laser controller
    DoublyNode* currentNode = lasersList->head;

    while(currentNode != NULL)
    {
        LaserUpdate((Laser*)currentNode->data);
    }
}

//deconstruct linked list and all laser controllers in list
void DeconstructAllLasers()
{
    //loop through all instances of laser controller
    DoublyNode* currentNode = lasersList->head;

    while(currentNode != NULL)
    {
        DeconstructLaser((Laser*)currentNode->data);
        DoublyLinkedListDeleteNode(lasersList, currentNode);
    }
}

#endif // LASER_H