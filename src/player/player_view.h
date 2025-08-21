#ifndef PLAYER_VIEW_H
#define PLAYER_VIEW_H
#include "misc.h"
#include "video.h"
#include "../sprite/sprite.h"

struct PlayerView
{
    Sprite** sprites; // pointer to list of pointers to sprites of the player
};

PlayerView* CreatePlayerView(Sprite** sprites)
{
    PlayerView* view = (PlayerView*)malloc(sizeof(PlayerView));
    view->sprites = sprites; // Initialize the sprite array
    return view;
}

void DeinitializePlayerView(PlayerView* view)
{
    // Deinitialize view properties here if needed
    free(view);
}

void DrawPlayer(PlayerView* view, Player* player)
{
}

#endif // PLAYER_VIEW_H