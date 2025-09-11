#ifndef LASER_H
#define LASER_H
#include "misc.h"
#include "video.h"
#include "../vector/vector2.h"
#include "../object.h"
#include "../data_structures/doubly_linked_list/doubly_linked_list.h"
#include "weapon.h"
#include "../tools/debugger.h"

//initialize instances list
DoublyLinkedList* laserList = CreateDoublyLinkedList();
int laserIdCounter = 0;

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
    InitializeObject(&laser->object, name, textureID, regionID, laserIdCounter++, x, y, isActive, speed);
    laser->type = type;
    laser->lifetime = lifetime;
    laser->age = 0.0;

    DoublyLinkedListInsertAtTail(laserList, &laser->object);

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
    laser->age += 1.0 / 60.0;
    if(laser->age > laser->lifetime)
    {
        laser->object.status |= DeletionMarkFlag;
    }

    //draw
    DrawLaser(laser);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 4: INSTANCES MANAGEMENT////////////////////
///////////////////////////////////////////////////////////
//=========================================================

//return linked list of lasers
DoublyLinkedList* GetLaserList()
{
    return laserList;
}

//update all laser controller in the laser controller list
void UpdateAllLasers()
{
    //loop through all instances of laser controller
    DoublyNode* currentNode = laserList->head;

    while(currentNode != NULL)
    {
        if(currentNode->data != NULL)
        {
            LaserUpdate((Laser*)currentNode->data);
            if(currentNode->data->status & DeletionMarkFlag)
            //if(false)
            {
                DoublyNode* temp = currentNode;
                currentNode = currentNode->next;

                DeconstructLaser((Laser*)temp->data);
                DoublyLinkedListDeleteNode(laserList, temp);
            }
            else
            {
                currentNode = currentNode->next;
            }
        }
        else
        {
            currentNode = currentNode->next;
        }
    }
}

//deconstruct linked list and all laser controllers in list
void DeconstructAllLasers()
{
    //loop through all instances of laser controller
    DoublyNode* currentNode = laserList->head;
    DoublyNode* next;

    while(currentNode != NULL)
    {
        next = currentNode->next;
        DeconstructLaser((Laser*)currentNode->data);
        DoublyLinkedListDeleteNode(laserList, currentNode);

        currentNode = next;
    }
}

#endif // LASER_H