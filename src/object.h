#ifndef _OBJECT_H
#define _OBJECT_H

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
  bool        isActive;
};

// This function is mainly for our embedded object 
void    initObject (Object* obj, ObjectType objT, int textureID, int regionID, int xPos, int yPos, bool isActive)
{
    obj -> type       = objT;
    obj -> textureID  = textureID;
    obj -> regionID   = regionID;
    obj -> x          = xPos;
    obj -> y          = yPos;
    obj -> vx         = 1; // Set to 1 for now, will make it customizable eventually
    obj -> vy         = 1;
    obj -> isActive   = isActive;
}

Object *createObject (int textureID, int regionID, int x, int y, bool isActive)
{
    Object *obj       = (Object *) malloc (sizeof (Object));
    obj -> type       = Object_Type_None; // Has no parent
    obj -> textureID  = textureID;
    obj -> regionID   = regionID;
    obj -> x          = x;
    obj -> y          = y;
    obj -> isActive   = isActive;

    return (obj);
}

#endif
