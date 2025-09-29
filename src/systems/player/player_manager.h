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
void InitializePlayer(PlayerController* player);
PlayerController* ConstructPlayerController();
void DeconstructPlayerController(PlayerController* player);
void UpdatePlayerController(PlayerController* player);


#endif //PLAYER_MANAGER_H