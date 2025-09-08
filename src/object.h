#ifndef OBJECT_H
#define OBJECT_H
#include "string.h"
#include "video.h"

////////////////////////////////////////////////////////////////
///////////Struct///////////////////////////////////////////////
////////////////////////////////////////////////////////////////

struct Object
{
    int* name; //string for name of object
    int textureID; //texture id
    int regionID; //region id
    int id; //object id
    int x; //x
    int y; //y
    float xdir; //input direction x
    float ydir; //input direction y
    bool isActive; //active in scene
    int speed; //speed in scene
};

////////////////////////////////////////////////////////////////
///////////Constructor & Deconstructor//////////////////////////
////////////////////////////////////////////////////////////////

void InitializeObject(Object* object, int* name, int textureID, int regionID, int id, int x, int y, bool isActive, int speed)
{
    //copy the string that was passed in into the player name field
    int* playerName = (int*)malloc(sizeof(int) * (strlen(name) + 1));
    strcpy(playerName, name); 

    //initialize object fields
    object->name = playerName;
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

Object* CreateObject(int* name, int textureID, int regionID, int id, int x, int y, bool isActive, int speed)
{
    //malloc object and initialize then return
    Object* object = (Object*)malloc(sizeof(Object));
    InitializeObject(object, name, textureID, regionID, id, x, y, isActive, speed);
    return object;
}

//string needs to be freed alongside the entire object
void DeconstructObject(Object* object)
{
    free(object->name);
    free(object);
}

////////////////////////////////////////////////////////////////
///////////Misc/////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

void DrawObject(Object* object)
{
    select_texture(object->textureID);
    select_region(object->regionID);
    draw_region_at(object->x, object->y);
}

#endif //OBJECT_H