#ifndef PLAYER_VIEW_H
#define PLAYER_VIEW_H
#include "misc.h"
#include "video.h"
#include "../sprite/sprite.h"

/** 
 * SUMMARY:
 * this file represents the view of a player
 * it contains functions to create, deinitialize and draw the player
**/

////////////////////////////////////////////////////////////
///////////Struct//////////////////////////////////////////
///////////////////////////////////////////////////////////

struct PlayerView
{
    Sprite** sprites; // pointers to all the sprites the player will use
    int numSprites; // number of sprites
};

///////////////////////////////////////////////////////////
///////////Constructor and Deconstructor///////////////////
///////////////////////////////////////////////////////////

PlayerView* CreatePlayerView(Sprite** sprites, int numSprites)
{
    PlayerView* view = (PlayerView*)malloc(sizeof(PlayerView));
    view->sprites = sprites; // Initialize the sprite array
    view->numSprites = numSprites;
    return view;
}

void DeconstructPlayerView(PlayerView* view)
{
    free(view);
}

///////////////////////////////////////////////////////////
///////////Player View Functions///////////////////////////
///////////////////////////////////////////////////////////

void DrawPlayer(PlayerView* view, Player* player)
{
}

#endif // PLAYER_VIEW_H