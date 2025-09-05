#ifndef PLAYER_MANAGER_H
#define PLAYER_MANAGER_H
#include "player_controller.h"
#include "player_model.h"
#include "player_view.h"
#include "../../architecture/component/component_manager.h"
#include "../../architecture/object/object_manager.h"
#include "../../data_structures/doubly_linked_list/doubly_linked_list.h"

//player linked list
DoublyLinkedList* playerComponentList = CreateDoublyLinkedList();

//=========================================================
///////////////////////////////////////////////////////////
///////////PLAYER CONTROLLER MANAGEMENT////////////////////
///////////////////////////////////////////////////////////
//=========================================================

/** 
 * SUMMARY:
 * This part keeps tracks of all the instances of player controller in a linked list, and provides functions to manage,
 * create, destroy, and update all player controllers.
**/

//return linked list of player controllers
DoublyLinkedList* GetPlayerList()
{
    return playerComponentList; 
}

//update all player controller in instances list
void UpdateAllPlayerControllers()
{
    DoublyNode* currentNode = playerList->head;
    Component* currentData = NULL;
    while(currentNode != NULL)
    {
        currentData = currentNode->data;
        if(currentData != NULL)
        {
            PlayerControllerUpdate((Component*)currentData);
        }
        currentNode = currentNode->next;
    }
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PLAYER MODEL CONSTRUCTION///////////////////////
///////////////////////////////////////////////////////////
//=========================================================

//initialize player model
void InitializePlayerModel(PlayerModel* playerModel, int* name, int speed, float maxShootCooldownTime)
{
    //player object properties initialization
    ObjectManagerInitializeObject(&playerModel->object, name);    

    //initialize passed in properties
    playerModel->maxShootCooldownTime = maxShootCooldownTime;
    playerModel->speed = speed;

    //intialize garbage values
    playerModel->state = PLAYER_MOVEMENT_STATE_IDLE; // Start in idle state
    playerModel->inputDirection.x = 0;
    playerModel->inputDirection.y = 0;
    playerModel->shootCooldownElapsed = 0; // Start with no cooldown
}

//construct player model
PlayerModel* ConstructPlayerModel(int* name, int speed, float maxShootCooldownTime)
{
    //allocate memory for player model
    PlayerModel* playerModel = (PlayerModel*)malloc(sizeof(PlayerModel));
    //initialize player model
    InitializePlayerModel(playerModel, name, speed, maxShootCooldownTime);
    //return player model
    return playerModel;
}

//deconstruct player model
void DeconstructPlayerModel(PlayerModel* playerModel)
{
    ObjectManagerDeconstructObject(playerModel->base);
    //free player model
    free(playerModel);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PLAYER CONTROLLER CONSTRUCTION//////////////////
///////////////////////////////////////////////////////////
//=========================================================

void InitializePlayerController(PlayerController* playerController, int* name, PlayerModel* playerModel, int gamepadID)
{
    //initialize as PLAYER_COMPONENT component enum
    ComponentManagerInitializeComponent(playerController->component, name, PLAYER_CONTROLLER_COMPONENT);
    playerController->playerModel = playerModel;
    playerController->gamepadID = gamepadID;
}

PlayerController* ConstructPlayerController(int* name, float speed, float maxShootCooldownTime, int gamepadID)
{
    //allocate player controller
    PlayerController* playerController = (PlayerController*)malloc(sizeof(PlayerController));
    //initialize player controller
    InitializePlayerController(playerController, ConstructPlayerModel(name, speed, maxShootCooldownTime), gamepadID);
    //return player controller
    return playerController;
}

//player controller deconstructor
void DeconstructPlayerController(PlayerController* playerController)
{
    //deconsruct component
    ComponentManagerDeconstructComponent(&playerController->component);
    //deconstruct player model
    DeconstructPlayerModel(playerController->playerModel);
    //free player controller struct
    free(playerController);
}

#endif //PLAYER_MANAGER_H