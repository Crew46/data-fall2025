#ifndef EXPLOSION_H
#define EXPLOSION_H
#include "misc.h"
#include "../object.h"

//initialize instances list
List* explosionList = createList();

struct Explosion {
    Object object;
    int damage;
    float lifetime; // Lifetime of the explosion in seconds
    float age;
};

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 1: Constructor and Deconstructor///////////
///////////////////////////////////////////////////////////
//=========================================================

Explosion* CreateExplosion(int textureID, int regionID, int x, int y, int status, int damage, float lifetime)
{
    Explosion* explosion = (Explosion*)malloc(sizeof(Explosion));
    initObject(&explosion->object, Object_Type_Explosion, textureID, regionID, x, y, status);
    explosion->damage = damage;
    explosion->lifetime = lifetime;
    explosion->age = 0.0;

    explosionList = append(explosionList, explosionList->tail, createNode(&explosion->object));

    return explosion;
}


//=========================================================
///////////////////////////////////////////////////////////
///////////PART 2: VISUAL FUNCTIONS////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void DrawExplosion(Explosion* explosion)
{
    drawObject(&explosion->object);
}

void DeconstructExplosion(Explosion* explosion)
{
    free(explosion);
}

void ExplosionUpdate(Explosion* explosion)
{
    //logical operations here
    explosion->age += 1.0/60.0 * (float)FRAME_SLICES;

    int frame = floor(explosion->age / explosion->lifetime * 5.0);
    explosion->object.regionID = EXPLODE_FRAME_0 + frame;

    if(explosion->age > explosion->lifetime)
    {
        explosion -> object.status |= DELETION_FLAG;
    }
}
//=========================================================
///////////////////////////////////////////////////////////
///////////PART 4: INSTANCES MANAGEMENT////////////////////
///////////////////////////////////////////////////////////
//=========================================================

//return linked list of explosions
List* GetExplosionList()
{
    return explosionList;
}

void UpdateAllExplosions()
{
    //loop through all instances of explosion controller
    Node* currentNode = explosionList->head;
    Node* nextNode;

    while(currentNode != NULL)
    {
        nextNode = currentNode->next;
        if(currentNode->data != NULL)
        {
            ExplosionUpdate((Explosion*)currentNode->data);
            if(currentNode->data->status & DELETION_FLAG)
            {
                DeconstructExplosion((Explosion*)currentNode->data);
                explosionList  = obtain(explosionList, &currentNode);
                deleteNode(currentNode);
            }
        }

        currentNode = nextNode;
    }
}

//deconstruct linked list and all laser controllers in list
void DeconstructAllExplosions()
{
    //loop through all instances of explosion controller
    Node* currentNode = explosionList->head;
    Node* next;

    while(currentNode != NULL)
    {
        next = currentNode->next;
        DeconstructExplosion((Explosion*)currentNode->data);
        explosionList  = obtain(explosionList, &currentNode);
        deleteNode(currentNode);

        currentNode = next;
    }
}

#endif // EXPLOSION_H
