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
    float x;
    float y;
    float xdir;
    float ydir;
    bool isActive;
    int speed;
};

////////////////////////////////////////////////////////////////
///////////Constructor & Deconstructor//////////////////////////
////////////////////////////////////////////////////////////////

Object* CreateObject(int textureID, int regionID, int id, int x, int y, bool isActive, int speed)
{
    //create instances of object and vector2
    Object* object = (Object*)malloc(sizeof(Object));

    //initialize object fields
    object->x = x;
    object->y = y;
    object->textureID = textureID;
    object->regionID = regionID;
    object->id = id;
    object->isActive = isActive;
    object->speed = speed;

    return object;
}

//object is composed, rather than aggregate of vector2, so also responsible for freeing it
void DeconstructObject(Object* object)
{
    free(object);
}

#endif //OBJECT_H