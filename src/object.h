#ifndef _OBJECT_H
#define _OBJECT_H

#include "math.h"

#define IsActiveFlag 0x00000001
#define DeletionMarkFlag 0x00000002
#define TeamFlagMask 0x000000C
#define TeamFlagOffset 2

#define ShipWidth 32
#define ShipHeight 32
#define LaserWidth 10
#define LaserHeight 20

// We need to know if the object is embedded so we can free memory properly
enum ObjectType
{
  Object_Type_None,
  Object_Type_Laser,
  Object_Type_Weapon,
  Object_Type_Entity
};

// Object struct which will be our base struct 
struct Object
{
  ObjectType  type;
  int         textureID;
  int         regionID;
  int         id;
  int         x;
  int         y;
  int         dx;
  int         dy;
  int         vx;
  int         vy;
  int         status;
};

// This function is mainly for our embedded object 
void    initObject (Object* obj, ObjectType objT, int textureID, int regionID, int xPos, int yPos, int status)
{
    obj -> type       = objT;
    obj -> textureID  = textureID;
    obj -> regionID   = regionID;
    obj -> x          = xPos;
    obj -> y          = yPos;
    obj -> dx         = 0;
    obj -> dy         = 0;
    obj -> vx         = 1; // Set to 1 for now, will make it customizable eventually
    obj -> vy         = 1;
    obj -> status     = status;
}

Object *createObject (int textureID, int regionID, int x, int y, int status)
{
    Object *obj       = (Object *) malloc (sizeof (Object));
    obj -> type       = Object_Type_None; // Has no parent
    obj -> textureID  = textureID;
    obj -> regionID   = regionID;
    obj -> x          = x;
    obj -> y          = y;
    obj -> status     = status;

    return (obj);
}

void drawObject(Object* object)
{
    select_texture(object->textureID);
    select_region(object->regionID);
    int team = (object->status & TeamFlagMask) >> TeamFlagOffset;

    set_drawing_angle((float)team * pi / 2.0);
    draw_region_rotated_at(object->x, object->y);
}

void moveObject(Object* object)
{
    object->x += object->dx;
    object->y += object->dy;
}

bool collisionCheck(Object* object1, Object* object2)
{
    int object1width;
    int object1height;
    int object2width;
    int object2height;

    if(object1->type == Object_Type_Entity)
    {
        object1width  = ShipWidth;
        object1height = ShipHeight;
    }
    else if(object1->type == Object_Type_Laser)
    {
        object1width  = LaserWidth;
        object1height = LaserHeight;
    }
    else
    {
        return false;
    }

    if(object2->type == Object_Type_Entity)
    {
        object2width  = ShipWidth;
        object2height = ShipHeight;
    }
    else if(object2->type == Object_Type_Laser)
    {
        object2width  = LaserWidth;
        object2height = LaserHeight;
    }
    else
    {
        return false;
    }

    if(((object1->status & TeamFlagMask) >> TeamFlagOffset) % 2 == 1)
    {
        object1width  ^= object1height;
        object1height ^= object1width;
        object1width  ^= object1height;
    }

    if(((object2->status & TeamFlagMask) >> TeamFlagOffset) % 2 == 1)
    {
        object2width  ^= object2height;
        object2height ^= object2width;
        object2width  ^= object2height;
    }

    int object1left   = object1->x - (object1width  / 2);
    int object1right  = object1->x + (object1width  / 2);
    int object1up     = object1->y - (object1height / 2);
    int object1down   = object1->y + (object1height / 2);

    int object2left   = object2->x - (object2width  / 2);
    int object2right  = object2->x + (object2width  / 2);
    int object2up     = object2->y - (object2height / 2);
    int object2down   = object2->y + (object2height / 2);

    if(object1left  >= object2right)
    {
        return false;
    }

    if(object1up    >= object2down)
    {
        return false;
    }

    if(object1right <= object2left)
    {
        return false;
    }

    if(object1down  <= object2up)
    {
        return false;
    }

    return true;
}

#endif
