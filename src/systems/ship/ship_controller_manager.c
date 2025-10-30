#ifndef SHIP_CONTROLLER_MANAGER_C
#define SHIP_CONTROLLER_MANAGER_C
#include "ship_controller_manager.h"
#include "../../architecture/component/component_manager.h"
#include "../audio/audio_manager.h"
#include "../input/input_controller_manager.h"
#include "../../tools/debugger.c"
#include "video.h"

//=========================================================
///////////////////////////////////////////////////////////
///////////PLAYER CONTROLLER CONSTRUCTION//////////////////
///////////////////////////////////////////////////////////
//=========================================================

void InitializeShipController(ShipController* player)
{
    CM_InitializeComponent((Component*)player, PLAYER_CONTROLLER_COMPONENT);
    player->state = PLAYER_MOVEMENT_STATE_IDLE;
}

ShipController* ConstructShipController()
{
    ShipController* player = (ShipController*)malloc(sizeof(ShipController));
    InitializeShipController(player);
    return player;
}

//player controller deconstructor
void DeconstructShipController(ShipController* player)
{
    CM_DeconstructComponent((Component*)player);
    free(player);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////BEHAVIOURAL FUNCTIONS///////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void UpdateShipController(ShipController* playerController)
{
    InputController* input = (InputController*)GOM_GameObjectGet_ComponentByType(((Component*)playerController)->gameObjectAttatchedTo, INPUT_CONTROLLER_COMPONENT);
    if(input)
    {
        TransformComponent* transform = (TransformComponent*)GOM_GameObjectGet_ComponentByType(((Component*)playerController)->gameObjectAttatchedTo, TRANSFORM_COMPONENT);
        Vector2* movement = ICM_InputControllerGet_NormalizedMovement(input);
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

        if(ICM_InputControllerGet_ValueOfButton(input, GAMEPAD_BUTTON_A) == 1)
        {
            //PlayRandomSFXOfType(EXPLOSION_SOUND_EFFECT);
            PlayRandomSFXOfType(LASER_SOUND_EFFECT);
        }

        if(ICM_InputControllerGet_ValueOfButton(input, GAMEPAD_BUTTON_B) == 1)
        {
            PlayRandomSFXOfType(EXPLOSION_SOUND_EFFECT);
        }
    }
}

#endif //SHIP_CONTROLLER_MANAGER_C