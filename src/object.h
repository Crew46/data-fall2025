#ifndef OBJECT_H
#define OBJECT_H
#include "string.h"
#include "video.h"
#include "math.h"
#include "vector/vector2.h"


#define IsActiveFlag 0x00000001
#define DeletionMarkFlag 0x00000002
#define TeamFlagMask 0x000000C
#define TeamFlagOffset 2

////////////////////////////////////////////////////////////////
///////////Struct///////////////////////////////////////////////
////////////////////////////////////////////////////////////////

struct Object
{
    int* name; //string for name of object
    int status; //Current status of the object
    int textureID; //texture id
    int regionID; //region id
    int id; //object id
    int x; //x
    int y; //y
    float xdir; //input direction x
    float ydir; //input direction y
    int speed; //speed in scene
};

////////////////////////////////////////////////////////////////
///////////Constructor & Deconstructor//////////////////////////
////////////////////////////////////////////////////////////////

void InitializeObject(Object* object, int* name, int textureID, int regionID, int id, int x, int y, bool isActive, int team, int speed)
{
    //copy the string that was passed in into the player name field
    int* playerName = (int*)malloc(sizeof(int) * (strlen(name) + 1));
    strcpy(playerName, name); 

    //initialize object fields
    object->name = playerName;

    object->status = 0;
    if(isActive)
    {
        object->status |= IsActiveFlag;
    }
    else
    {
        object->status &= ~IsActiveFlag;
    }
    object->status |= (team << TeamFlagOffset) & TeamFlagMask;

    object->x = x;
    object->y = y;
    object->textureID = textureID;
    object->regionID = regionID;
    object->id = id;
    object->speed = speed;

    //default values
    object->xdir = 0;
    object->ydir = 0;
}

Object* CreateObject(int* name, int textureID, int regionID, int id, int x, int y, bool isActive, int team, int speed)
{
    //malloc object and initialize then return
    Object* object = (Object*)malloc(sizeof(Object));
    InitializeObject(object, name, textureID, regionID, id, x, y, isActive, team, speed);
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
    int team = (object->status & TeamFlagMask) >> TeamFlagOffset;
    switch(team)
    {
        case 0:
            set_drawing_angle(0.0);
            break;
        case 1:
            set_drawing_angle(pi / 2.0);
            break;
        case 2:
            set_drawing_angle(pi);
            break;
        case 3:
            set_drawing_angle(3.0 * pi / 2.0);
            break;
        default:
            set_drawing_angle(0.0);
            break;
    }
    draw_region_rotated_at(object->x, object->y);
}

//move object in a direction, where then direction is scaled by the object's speed
void ObjectMoveInDirection(Object* object)
{
    float resultX;
    float resultY;
    //add object position and direction to object position
    MultiplyVector2ByScalar(object->xdir, object->ydir, object->speed, &resultX, &resultY); // Scale the movement vector by the object's speed
    float resultsX2;
    float resultsY2;
    AddVector2Components(resultX, object->x, resultY, object->y, &resultsX2, &resultsY2);
    object->x = round(resultsX2);
    object->y = round(resultsY2);
}

int StatusGetTeam(int status)
{
    return (status & TeamFlagMask) >> TeamFlagOffset;
}

#endif //OBJECT_H