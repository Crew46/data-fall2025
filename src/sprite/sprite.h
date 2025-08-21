#ifndef SPRITE_H
#define SPRITE_H
#include "misc.h"

struct Sprite
{
    int regionID; // ID of the texture region 
};

Sprite* CreateSprite(int regionID)
{
    Sprite* sprite = (Sprite*)malloc(sizeof(Sprite));
    sprite->regionID = regionID;
}

void DeinitializeSprite(Sprite* sprite)
{
    free(sprite);
}

#endif // SPRITE_H