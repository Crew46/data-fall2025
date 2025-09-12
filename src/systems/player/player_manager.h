#ifndef PLAYER_MANAGER_H
#define PLAYER_MANAGER_H
#include "../../data_structures/doubly_linked_list/doubly_linked_list.h"
#include "player.h"

struct PlayerManager
{
    DoublyLinkedList* playerControllerList;
}

void InitializePlayerManager();
void DeinitializePlayerManager();
void InitializePlayer(Player* player, float speed);
Player* ConstructPlayerController(float speed);
void DeconstructPlayerController();


#endif //PLAYER_MANAGER_H