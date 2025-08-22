#ifndef LASER_VIEW_H
#define LASER_VIEW_H
#include "../sprite/sprite.h"
#include "laser.h"

/** 
 * SUMMARY:
 * this files represents the view of the laser
 * it's struct contains all the sprites that the laser might need
 * it also contains functions to create, deinitialize and draw the laser
**/

struct LaserView
{
    Sprite** sprites;
    int numSprites;
};

///////////////////////////////////////////////////////////
///////////Constructor and Deconstructor///////////////////
///////////////////////////////////////////////////////////

LaserView* CreateLaserView(Sprite** sprites, int numSprites)
{
    LaserView* view = (LaserView*)malloc(sizeof(LaserView));
    view->sprites = sprites; // Initialize the sprite array
    view->numSprites = numSprites;
    return view;
}

void DeconstructLaserView(LaserView* view)
{
    free(view);
}

///////////////////////////////////////////////////////////
///////////Player View Functions///////////////////////////
///////////////////////////////////////////////////////////

void DrawLaser(LaserView* view, Laser* laser)
{
    //select texture and region for first sprite in sprite array
    select_texture(view->sprites[0]->textureID); // Select the lasers's texture
    select_region(view->sprites[0]->regionID); // Select the lasers's sprite region

    //draw the sprite at the player's position
    draw_region_at(laser->position->x, laser->position->y); // Draw the sprite at the player's position
}

#endif // LASER_VIEW_H