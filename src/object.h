#ifndef _OBJECT_H
#define _OBJECT_H
#include "math.h"

////////////////////////////////////////////////////////////////////////////////////
//
// Object API
// ======================
// void    initObject    (Object     *obj,
//                        ObjectType  objT,
//                        int         textureID,
//                        int         regionID,
//                        int         xPos,
//                        int         yPos,
//                        int         status);
// Object *createObject  (int         textureID,
//                        int         regionID,
//                        int         x,
//                        int         y,
//                        int         status);
// void    drawObject    (Object     *object);
// void    moveObject    (Object     *object);
// bool    collisionCheck(Object     *object1,
//                        Object     *object2);
//
////////////////////////////////////////////////////////////////////////////////////

#define INACTIVE_FLAG  0x00000000
#define IS_ACTIVE_FLAG 0x00000001
#define DELETION_FLAG  0x00000002
#define ODD_TEAM_FLAG  0x00000004
#define HIGH_TEAM_FLAG 0x00000008
#define ODD_HIGH_FLAG  0x0000000C
#define ZOOM_FLAG      0x00000010
#define TeamFlagMask   0x000000C
#define TeamFlagOffset 2

#define SHIPWIDTH       64
#define SHIPHEIGHT      64
#define LASERWIDTH      10
#define LASERHEIGHT     20
#define MISSILEWIDTH    10
#define MISSILEHEIGHT   20
#define EXPLOSIONWIDTH  40
#define EXPLOSIONHEIGHT 40
#define WEAPONWIDTH     10
#define WEAPONHEIGHT    10

// We need to know if the object is embedded so we can free memory properly
enum ObjectType
{
    Object_Type_None,
    Object_Type_Laser,
    Object_Type_Missile,
    Object_Type_Explosion,
    Object_Type_Weapon,
    Object_Type_Entity
};

// Object struct which will be our base struct 
struct Object
{
    ObjectType  type;
    int         textureID;
    int         regionID;
    int         frame;
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

void  drawObject (Object *object)
{
    int team            = 0;

    if (IS_ACTIVE_FLAG == (object -> status & IS_ACTIVE_FLAG))
    {
        select_texture (object -> textureID);
        select_region  (object -> regionID);

        team            = (object -> status & TeamFlagMask) >> TeamFlagOffset;

        set_drawing_angle ((float) team * pi / 2.0);

        if (ZOOM_FLAG  == (object -> status & ZOOM_FLAG))
        {
            set_drawing_scale (0.25, 0.25);
        }
        else
        {
            set_drawing_scale (1.00, 1.00);
        }    

        draw_region_rotozoomed_at (object -> x, object -> y);
    }
}

void  moveObject (Object *object)
{
    object -> x  = object -> x + (object -> dx * FRAME_SLICES);
    object -> y  = object -> y + (object -> dy * FRAME_SLICES);
}

bool  collisionCheck (Object *object1, Object *object2)
{
    int  object1width         = 0;
    int  object1height        = 0;
    int  object1left          = 0;
    int  object1right         = 0;
    int  object1up            = 0;
    int  object1down          = 0;
    int  object2width         = 0;
    int  object2height        = 0;
    int  object2left          = 0;
    int  object2right         = 0;
    int  object2up            = 0;
    int  object2down          = 0;
    int  result               = 0;

    if (object1 -> type      == Object_Type_Entity)
    {
        object1width          = SHIPWIDTH;
        object1height         = SHIPHEIGHT;
    }
    else if (object1 -> type == Object_Type_Laser)
    {
        object1width          = LASERWIDTH;
        object1height         = LASERHEIGHT;
    }
    else if (object1 -> type == Object_Type_Missile)
    {
        object1width          = MISSILEWIDTH;
        object1height         = MISSILEHEIGHT;
    }
    else if (object1 -> type == Object_Type_Explosion)
    {
        object1width          = EXPLOSIONWIDTH;
        object1height         = EXPLOSIONHEIGHT;
    }
    else if (object1 -> type == Object_Type_Weapon)
    {
        object1width          = WEAPONWIDTH;
        object1height         = WEAPONHEIGHT;
    }
    else
    {
        return (false);
    }

    if (object2 -> type      == Object_Type_Entity)
    {
        object2width          = SHIPWIDTH;
        object2height         = SHIPHEIGHT;
    }
    else if (object2 -> type == Object_Type_Laser)
    {
        object2width          = LASERWIDTH;
        object2height         = LASERHEIGHT;
    }
    else if (object2 -> type == Object_Type_Missile)
    {
        object2width          = MISSILEWIDTH;
        object2height         = MISSILEHEIGHT;
    }
    else if (object2 -> type == Object_Type_Explosion)
    {
        object2width          = EXPLOSIONWIDTH;
        object2height         = EXPLOSIONHEIGHT;
    }
    else if (object2 -> type == Object_Type_Weapon)
    {
        object2width          = WEAPONWIDTH;
        object2height         = WEAPONHEIGHT;
    }
    else
    {
        return (false);
    }

    result                    = object1 -> status & TeamFlagMask;
    result                    = result >> TeamFlagOffset;
    if ((result % 2)         == 1)
    {
        object1width          = object1width  ^ object1height;
        object1height         = object1height ^ object1width;
        object1width          = object1width  ^ object1height;
    }

    result                    = object2 -> status & TeamFlagMask;
    result                    = result >> TeamFlagOffset;
    if ((result % 2)         == 1)
    {
        object2width          = object2width  ^ object2height;
        object2height         = object2height ^ object2width;
        object2width          = object2width  ^ object2height;
    }

    object1left               = object1 -> x  - (object1width  / 2);
    object1right              = object1 -> x  + (object1width  / 2);
    object1up                 = object1 -> y  - (object1height / 2);
    object1down               = object1 -> y  + (object1height / 2);

    object2left               = object2 -> x  - (object2width  / 2);
    object2right              = object2 -> x  + (object2width  / 2);
    object2up                 = object2 -> y  - (object2height / 2);
    object2down               = object2 -> y  + (object2height / 2);

    if (object1left          >= object2right)
    {
        return (false);
    }

    if (object1up            >= object2down)
    {
        return (false);
    }

    if (object1right         <= object2left)
    {
        return (false);
    }

    if (object1down          <= object2up)
    {
        return (false);
    }

    return (true);
}

#endif
