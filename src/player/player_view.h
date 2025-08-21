#ifndef PLAYER_VIEW_H
#define PLAYER_VIEW_H
#include "misc.h"
#include "video.h"
#include "../sprite/sprite.h"

struct PlayerView
{
    Sprite** sprites; // pointers to all the sprites the player will use
    int numSprites; // number of sprites
};

PlayerView* CreatePlayerView(Sprite** sprites)
{
    PlayerView* view = (PlayerView*)malloc(sizeof(PlayerView));
    view->sprites = sprites; // Initialize the sprite array
    return view;
}

void DeinitializePlayerView(PlayerView* view)
{
    for(int i = 0; i < view->numSprites; i++)
    {
        DeinitializeSprite(view->sprites[i]); // Deinitialize each sprite
    }
    free(view);
}

void DrawPlayer(PlayerView* view, Player* player)
{
}

#endif // PLAYER_VIEW_H