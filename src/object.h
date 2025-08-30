#ifndef OBJECT_H
#define OBJECT_H
#include "vector/vector2.h"

////////////////////////////////////////////////////////////////
///////////Struct///////////////////////////////////////////////
////////////////////////////////////////////////////////////////

struct Object
{
    int textureID;
    int regionID;
    int id;
    int x;
    int y;
    float xdir;
    float ydir;
    bool isActive;
    int speed;
};

////////////////////////////////////////////////////////////////
///////////Constructor & Deconstructor//////////////////////////
////////////////////////////////////////////////////////////////

void InitializeObject(Object* object, int textureID, int regionID, int id, int x, int y, bool isActive, int speed)
{
    //initialize object fields
    object->x = x;
    object->y = y;
    object->textureID = textureID;
    object->regionID = regionID;
    object->id = id;
    object->isActive = isActive;
    object->speed = speed;

    //default values
    object->xdir = 0;
    object->ydir = 0;
}

Object* CreateObject(int textureID, int regionID, int id, int x, int y, bool isActive, int speed)
{
    //malloc object and initialize then return
    Object* object = (Object*)malloc(sizeof(Object));
    InitializeObject(object, textureID, regionID, id, x, y, isActive, speed);
    return object;
}

//object is composed, rather than aggregate of vector2, so also responsible for freeing it
void DeconstructObject(Object* object)
{
    free(object);
}

#endif //OBJECT_H