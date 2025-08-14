#ifndef PLAYER_H
#define PLAYER_H

struct Player
{
    int x;
    int y;
    int health;
};

Player* CreatePlayer();

InitializePlayer(Player* player, int x, int y, int health);

DeInitializePlayer(Player* player);

void UpdatePlayer(Player* player);

void DrawPlayer(Player* player);

#endif // PLAYER_H
