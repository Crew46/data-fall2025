#ifndef LASER_H // laser.h
#define LASER_H

struct Object;
///////////////////////////////////////////////////////////////////////
//
// Laser structure
//
struct Laser
{
  Object obj;
};

Laser* createLaser(int textureID, int regionID, int x, int y, bool isActive)
{
  Laser* laser = (Laser*)malloc(sizeof(Laser));
  initObject(&laser->obj, Object_Type_Laser, textureID, regionID, x, y, isActive);

  // Set these manually for now
  laser->obj.dx = 0;
  laser->obj.vx = 1;
  laser->obj.dy = -1;
  laser->obj.vy = 5;
  return laser;
}

#endif
