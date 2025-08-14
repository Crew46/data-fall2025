#include "player.h"

Player* CreatePlayer()
{
    return (Player*)malloc(sizeof(Player));
}

void InitializePlayer(Player* player, int x, int y, int health)
{
    player->x = x;
    player->y = y;
    player->health = health;
}

void DeInitializePlayer(Player* player)
{
    free(player);
}

void UpdatePlayer(Player* player)
{

}

void DrawPlayer(Player* player)
{

}
