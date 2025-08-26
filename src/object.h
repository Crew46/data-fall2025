#ifndef OBJECT_H
#define OBJECT_H
#include "vector/vector2.h"
#include "sprite/sprite.h"

////////////////////////////////////////////////////////////////
///////////Struct///////////////////////////////////////////////
////////////////////////////////////////////////////////////////

struct Object
{
	int textureID;
	int regionID;
    int id;
    Vector2* position; //x & y
	int x;
	int y;
	int xdir;
	int ydir;
    bool isActive;
	int speed;
};

////////////////////////////////////////////////////////////////
///////////Constructor & Deconstructor//////////////////////////
////////////////////////////////////////////////////////////////

Object* CreateObject(int id, int x, int y, bool isActive)
{
    //create instances of object and vector2
    Object* object = (Object*)malloc(sizeof(Object));
    Vector2* position = CreateVector2(x, y);

    //initialize object fields
    object->position = position;
    object->id = id;
    object->isActive = isActive;

    return object;
}

void DeconstructObject(Object* object)
{
    free(object->position);
    free(object);
}

#endif //OBJECT_H
