#ifndef OBJECT_H
#define OBJECT_H

#define INACTIVE_FLAG  0x00000000
#define IS_ACTIVE_FLAG 0x00000001

struct Weapon;
struct Laser;
struct Entity;
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
void initObject(Object* obj, ObjectType objT, int textureID, int regionID, int xPos, int yPos, int status)
{
  obj->type       = objT;
  obj->textureID  = textureID;
  obj->regionID   = regionID;
  obj->x          = xPos;
  obj->y          = yPos;
  obj->vx         = 1; // Set to 1 for now, will make it customizable eventually
  obj->vy         = 1;
  obj->status     = status;

}

Object* createObject(int textureID, int regionID, int x, int y, int status)
{
  Object* obj     = (Object*)malloc(sizeof(Object));
  obj->type       = Object_Type_None; // Has no parent
  obj->textureID  = textureID;
  obj->regionID   = regionID;
  obj->x          = x;
  obj->y          = y;
  obj->status     = status;

  return obj;
}

void deleteObject(Object** obj)
{

  switch((*obj)->type)
  {
    case Object_Type_None: {
      free(*obj);
      break;
    }
    case Object_Type_Laser: {
      Laser* laser = (Laser*)*obj;
      free(laser);
      break;
    }
    case Object_Type_Weapon: {
      Weapon* weapon = (Weapon*)*obj;
      free(weapon);
      break;
    }
    case Object_Type_Entity: {
      Entity* entity = (Entity*)*obj;
      free(entity);
      break;
    }
    default:
      break;
  }
  *obj = NULL;
}


// Checks bounds but should only be used for objects that don't need to check which side they are exceeding
bool exceedsBounds(Object* obj)
{
  if(obj->x < 0 || obj->x > SCREEN_WIDTH)
    return true;
  if(obj->y < 0 || obj->y > SCREEN_HEIGHT)
    return true;

  return false;
}

void moveObject(Object* obj, int dx, int dy)
{
  obj  -> dx    = dx;
  obj  -> dy    = dy;
  obj  -> x     = obj  -> x + obj  -> dx * obj->vx;
  obj  -> y     = obj  -> y + obj  -> dy * obj->vy;
}


bool checkObjectCollision(Object* objA, Object* objB, int objA_Width, int objB_Width, int objA_Height, int objB_Height)
{
  // Check if objects are NULL
  if(!objA || !objB)
    return false;

  // Make collision less sensitive
  int cushion = 2;

  int aLeft   = objA->x + cushion;
  int aRight  = objA->x + objA_Width - cushion;
  int aTop    = objA->y + cushion;
  int aBottom = objA->y + objA_Height - cushion;

  int bLeft   = objB->x;
  int bRight  = objB->x + objB_Width;
  int bTop    = objB->y;
  int bBottom = objB->y + objB_Height;


  if( aLeft <= bRight
      && aRight >= bLeft
      && aBottom >= bTop
      && aTop <= bBottom) {

    return true;
  }

  return false;
}

void drawObject(Object* obj)
{
  select_texture ( obj->textureID );
  select_region  ( obj->regionID );
  draw_region_at ( obj->x, obj->y );
}

#endif //OBJECT_H
