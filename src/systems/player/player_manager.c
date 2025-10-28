#ifndef PLAYER_MANAGER_C
#define PLAYER_MANAGER_C
#include "player_manager.h"
#include "../../architecture/component/component_manager.h"

PlayerManager* playerManager;

//=========================================================
///////////////////////////////////////////////////////////
///////////PLAYER MANAGER INITIALIZATION//////////////////
///////////////////////////////////////////////////////////
//=========================================================

void InitializePlayerManager()
{
    playerManager = (PlayerManager*)malloc(sizeof(PlayerManager));
}

void DeinitializePlayerManager()
{
    //free linked list
    free(playerManager);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PLAYER CONTROLLER CONSTRUCTION//////////////////
///////////////////////////////////////////////////////////
//=========================================================

void InitializePlayer(PlayerController* player)
{
    ComponentManagerInitializeComponent((Component*)player, PLAYER_CONTROLLER_COMPONENT);
    player->state = PLAYER_MOVEMENT_STATE_IDLE;
}

PlayerController* ConstructPlayerController()
{
    PlayerController* player = (PlayerController*)malloc(sizeof(PlayerController));
    InitializePlayer(player);
    return player;
}

//player controller deconstructor
void DeconstructPlayerController(PlayerController* player)
{
    ComponentManagerDeconstructComponent((Component*)player);
    free(player);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////BEHAVIOURAL FUNCTIONS///////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void UpdatePlayerController(PlayerController* playerController)
{
    //if this component is attatched to an object
    if(((Component*)playerController)->gameObject != NULL)
    {
        TransformComponent* transform = (TransformComponent*)GameObjectManagerGameObjectGetComponentByType(((Component*)playerController)->gameObject, TRANSFORM_COMPONENT);
        Vector2* movement = CreateVector2(0, 0);
        gamepad_direction_normalized(&movement->x, &movement->y);
        Vector2* result = CreateVector2(0, 0);
        int speed = 8;
        MultiplyVector2ByScalar(movement, speed, result);
        Vector2* result2 = CreateVector2(0, 0);
        AddVector2Components(&transform->position, result, result2);
        TransformComponentSetGlobalPosition(transform, result2->x, result2->y);
        free(result);
        free(result2);
    }
}

#endif //PLAYER_MANAGER_C