#ifndef PLAYER_VIEW_H
#define PLAYER_VIEW_H
#include "misc.h"

struct PlayerView
{
    // Placeholder for player view properties (e.g., sprite, texture)
};

PlayerView* CreatePlayerView()
{
    PlayerView* view = (PlayerView*)malloc(sizeof(PlayerView));
    // Initialize view properties here if needed
    return view;
}

void DeinitializePlayerView(PlayerView* view)
{
    // Deinitialize view properties here if needed
    free(view);
}

#endif // PLAYER_VIEW_H