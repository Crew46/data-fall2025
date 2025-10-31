#ifndef DEFAULT_ENEMY_SHIP_STRATEGY_C
#define DEFAULT_ENEMY_SHIP_STRATEGY_C
#include "../ship_controller_manager.h"
#include "../../../architecture/game_object/game_object_manager.h"
#include "../../input/input_controller_manager.h"
#include "../../../vector/vector2.h"
#include "../../audio/audio_manager.h"

void UpdateDefaultShipStrategy(ShipController* controller)
{
    InputController* input = (InputController*)GOM_GameObjectGet_ComponentByType(((Component*)controller)->gameObjectAttatchedTo, INPUT_CONTROLLER_COMPONENT);
    if(input)
    {
        TransformComponent* transform = (TransformComponent*)GOM_GameObjectGet_ComponentByType(((Component*)controller)->gameObjectAttatchedTo, TRANSFORM_COMPONENT);
        Vector2* movement = ICM_InputControllerGet_NormalizedMovement(input);
        Vector2* result = CreateVector2(0, 0);
        MultiplyVector2ByScalar(movement, controller->speed, result);
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

#endif //DEFAULT_ENEMY_SHIP_STRATEGY_C