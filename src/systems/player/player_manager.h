#ifndef PLAYER_MANAGER_H
#define PLAYER_MANAGER_H
#include "../../data_structures/doubly_linked_list/doubly_linked_list.h"
#include "player_controller.h"

struct PlayerManager
{
    DoublyLinkedList* playerControllerList;
};

void InitializePlayerManager();
void DeinitializePlayerManager();
void InitializePlayer(Player* player);
Player* ConstructPlayerController();
void DeconstructPlayerController(Player* player);
void UpdatePlayerController(Player* player);


#endif //PLAYER_MANAGER_H