#ifndef PLAYER_CONTROLLER_MANAGER_C
#define PLAYER_CONTROLLER_MANAGER_C
#include "player_controller_manager.h"
#include "../../architecture/component/component_manager.h"
#include "../audio/audio_manager.h"
#include "../input/input_controller_manager.h"
#include "../../tools/debugger.c"
#include "video.h"

PlayerControllerManager* playerManager;

//=========================================================
///////////////////////////////////////////////////////////
///////////PLAYER MANAGER INITIALIZATION//////////////////
///////////////////////////////////////////////////////////
//=========================================================

void InitializePlayerControllerManager()
{
    playerManager = (PlayerControllerManager*)malloc(sizeof(PlayerControllerManager));
}

void DeinitializePlayerControllerManager()
{
    //free linked list
    free(playerManager);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PLAYER CONTROLLER CONSTRUCTION//////////////////
///////////////////////////////////////////////////////////
//=========================================================

void InitializePlayerController(PlayerController* player)
{
    CM_InitializeComponent((Component*)player, PLAYER_CONTROLLER_COMPONENT);
    player->state = PLAYER_MOVEMENT_STATE_IDLE;
}

PlayerController* ConstructPlayerController()
{
    PlayerController* player = (PlayerController*)malloc(sizeof(PlayerController));
    InitializePlayerController(player);
    return player;
}

//player controller deconstructor
void DeconstructPlayerController(PlayerController* player)
{
    CM_DeconstructComponent((Component*)player);
    free(player);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////BEHAVIOURAL FUNCTIONS///////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void UpdatePlayerController(PlayerController* playerController)
{
    InputController* input = (InputController*)GameObjectManagerGameObjectGetComponentByType(((Component*)playerController)->gameObjectAttatchedTo, INPUT_CONTROLLER_COMPONENT);
    if(input)
    {
        TransformComponent* transform = (TransformComponent*)GameObjectManagerGameObjectGetComponentByType(((Component*)playerController)->gameObjectAttatchedTo, TRANSFORM_COMPONENT);
        Vector2* movement = InputManagerGetNormalizedMovementOfInputController(input);
        Vector2* result = CreateVector2(0, 0);
        int speed = 8;
        MultiplyVector2ByScalar(movement, speed, result);
        Vector2* result2 = CreateVector2(0, 0);
        AddVector2Components(&transform->position, result, result2);
        if(result2->x < screen_width - 20 && result2->x > 0 + 20)
        {
            transform->position.x = result2->x;            
        }
        if(result2->y > 0 + 20 && result2->y < screen_height - 20)
        {
            transform->position.y = result2->y;            
        }
        free(result);
        free(result2);

        if(InputManagerGetButtonValueOfInputController(input, GAMEPAD_BUTTON_A) == 1)
        {
            //PlayRandomSFXOfType(EXPLOSION_SOUND_EFFECT);
            PlayRandomSFXOfType(LASER_SOUND_EFFECT);
        }
    }
}

#endif //PLAYER_MANAGER_C