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
List* laserList = createList();

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

Laser* CreateLaser(int textureID, int regionID, int x, int y, int status, LaserType type, float lifetime)
{
    Laser* laser = (Laser*)malloc(sizeof(Laser));
    initObject(&laser->object, Object_Type_Laser, textureID, regionID, x, y, status);
    laser->type = type;
    laser->lifetime = lifetime;
    laser->age = 0.0;

    laserList = append(laserList, laserList->tail, createNode(&laser->object));

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
    drawObject(&laser->object);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 3: LOGICAL CONNECTION//////////////////////
///////////////////////////////////////////////////////////
//=========================================================

//move laser in a direction, where then direction is scaled by the laser's speed
void LaserMoveInDirection(Laser* laser)
{
    moveObject(&laser->object);
}

void LaserUpdate(Laser* laser)
{
    //logical operations here
    laser->age += 1.0 / 60.0;
    if(laser->age > laser->lifetime)
    {
        laser->object.status |= DeletionMarkFlag;
    }

    int team = (laser->object.status & TeamFlagMask) >> TeamFlagOffset;

    if(team      == 0)
    {
        laser->object.dx = 0.0;
        laser->object.dy = -1.0;
    }
    else if(team == 1)
    {
        laser->object.dx = 1.0;
        laser->object.dy = 0.0;
    }
    else if(team == 2)
    {
        laser->object.dx = 0.0;
        laser->object.dy = 1.0;
    }
    else if(team == 3)
    {
        laser->object.dx = -1.0;
        laser->object.dy = 0.0;
    }

    LaserMoveInDirection(laser);

    //draw
    DrawLaser(laser);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 4: INSTANCES MANAGEMENT////////////////////
///////////////////////////////////////////////////////////
//=========================================================

//return linked list of lasers
List* GetLaserList()
{
    return laserList;
}

//update all laser controller in the laser controller list
void UpdateAllLasers()
{
    //loop through all instances of laser controller
    Node* currentNode = laserList->head;
    Node* nextNode;

    while(currentNode != NULL)
    {
        nextNode = currentNode->next;
        if(currentNode->data != NULL)
        {
            LaserUpdate((Laser*)currentNode->data);
            if(currentNode->data->status & DeletionMarkFlag)
            {
                DeconstructLaser((Laser*)currentNode->data);
                obtain(laserList, currentNode);
                deleteNode(currentNode);
            }
        }
        currentNode = nextNode;
    }
}

//deconstruct linked list and all laser controllers in list
void DeconstructAllLasers()
{
    //loop through all instances of laser controller
    Node* currentNode = laserList->head;
    Node* next;

    while(currentNode != NULL)
    {
        next = currentNode->next;
        DeconstructLaser((Laser*)currentNode->data);
        obtain(laserList, currentNode);
        deleteNode(currentNode);

        currentNode = next;
    }
}

#endif // LASER_H