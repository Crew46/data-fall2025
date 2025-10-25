#ifndef MISSILE_H
#define MISSILE_H
#include "misc.h"
#include "video.h"
#include "../vector/vector2.h"
#include "../object.h"
#include "../data_structures/doubly_linked_list/doubly_linked_list.h"
#include "../tools/debugger.h"
#include "weapon.h"
#include "explosion.h"

//initialize instances list
List* missileList = createList();

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 1: MODEL///////////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

/////////////////////////////////////////////////
///////////1: Struct/////////////////////////////
/////////////////////////////////////////////////

struct Missile {
    Object object;
    ProjectileType type;
    float lifetime; // Lifetime of the missile in seconds
    float age;
    bool explode;
};


/////////////////////////////////////////////////
///////////1: Constructor and Deconstructor//////
/////////////////////////////////////////////////

Missile* CreateMissile(int textureID, int regionID, int x, int y, int status, ProjectileType type, float lifetime)
{
    Missile* missile = (Missile*)malloc(sizeof(Missile));
    initObject(&missile->object, Object_Type_Missile, textureID, regionID, x, y, status);
    missile->type = type;
    missile->lifetime = lifetime;
    missile->age = 0.0;
    missile->explode = false;

    missileList = append(missileList, missileList->tail, createNode(&missile->object));

    return missile;
}

void DeconstructMissile(Missile* missile)
{
    free(missile);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 2: VISUAL FUNCTIONS////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void DrawMissile(Missile* missile)
{
    drawObject(&missile->object);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 3: LOGICAL CONNECTION//////////////////////
///////////////////////////////////////////////////////////
//=========================================================

//move missile in a direction, where then direction is scaled by the missile's speed
void MissileMoveInDirection(Missile* missile)
{
    moveObject(&missile->object);
}

void MissileUpdate(Missile* missile)
{
    //logical operations here
    missile->age += 1.0 / 60.0 * (float)FRAME_SLICES;
    if(missile->age > missile->lifetime)
    {
        missile->explode = true;
    }

    int team = (missile->object.status & TeamFlagMask) >> TeamFlagOffset;

    if(team      == 0)
    {
        missile->object.dx = 0.0;
        missile->object.dy = -1.0;
    }
    else if(team == 1)
    {
        missile->object.dx = 1.0;
        missile->object.dy = 0.0;
    }
    else if(team == 2)
    {
        missile->object.dx = 0.0;
        missile->object.dy = 1.0;
    }
    else if(team == 3)
    {
        missile->object.dx = -1.0;
        missile->object.dy = 0.0;
    }

    MissileMoveInDirection(missile);

    if(missile->explode)
    {
        CreateExplosion(EXPLOSION_TEXTURE, EXPLODE_FRAME_3, missile->object.x, missile->object.y, missile->object.status, 5, 1.0);
        missile->object.status |= DELETION_FLAG;
    }
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 4: INSTANCES MANAGEMENT////////////////////
///////////////////////////////////////////////////////////
//=========================================================

//return linked list of missiles
List* GetMissileList()
{
    return missileList;
}

//update all missile controller in the missile controller list
void UpdateAllMissiles()
{
    //loop through all instances of missile controller
    Node* currentNode = missileList->head;
    Node* nextNode;

    while(currentNode != NULL)
    {
        nextNode = currentNode->next;
        if(currentNode->data != NULL)
        {
            MissileUpdate((Missile*)currentNode->data);
            if(currentNode->data->status & DELETION_FLAG)
            {
                DeconstructMissile((Missile*)currentNode->data);
                missileList  = obtain(missileList, &currentNode);
                deleteNode(currentNode);
            }
        }
        currentNode = nextNode;
    }
}

//deconstruct linked list and all missile controllers in list
void DeconstructAllMissiles()
{
    //loop through all instances of missile controller
    Node* currentNode = missileList->head;
    Node* next;

    while(currentNode != NULL)
    {
        next = currentNode->next;
        DeconstructMissile((Missile*)currentNode->data);
        missileList  = obtain(missileList, &currentNode);
        deleteNode(currentNode);

        currentNode = next;
    }
}

#endif // MISSILE_H
