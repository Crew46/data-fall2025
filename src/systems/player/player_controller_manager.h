#ifndef PLAYER_CONTROLLER_MANAGER_H
#define PLAYER_CONTROLLER_MANAGER_H
#include "../../data_structures/doubly_linked_list/doubly_linked_list.h"
#include "player_controller.h"

struct PlayerControllerManager
{
    DoublyLinkedList* playerControllerList;
};

void InitializePlayerControllerManager();
void DeinitializePlayerControllerManager();
void InitializePlayerController(PlayerController* player);
PlayerController* ConstructPlayerController();
void DeconstructPlayerController(PlayerController* player);
void UpdatePlayerController(PlayerController* player);
void SetPlayerControllerGamepadID(PlayerController* playerController, int id);


#endif //PLAYER_MANAGER_H