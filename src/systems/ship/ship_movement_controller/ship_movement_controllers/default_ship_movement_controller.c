#ifndef DEFAULT_SHIP_MOVEMENT_CONTROLLER_C
#define DEFAULT_SHIP_MOVEMENT_CONTROLLER_C
#include "../ship_movement_controller.h"
#include "../../../input/input_controller_manager.h"
#include "../../../../tools/debugger.c"

struct DefaultShipMovementController
{
    ShipMovementController base;
};

void DefaultShipMovementControllerUpdate(DefaultShipMovementController* controller)
{
    PrintIntAt(screen_width - 400, screen_height -20, controller->base.speed);
    InputController* input = (InputController*)GOM_GameObjectGet_ComponentByType(((Component*)controller)->gameObjectAttatchedTo, INPUT_CONTROLLER_COMPONENT);
    if(input && controller)
    {
        TransformComponent* transform = (TransformComponent*)GOM_GameObjectGet_ComponentByType(((Component*)controller)->gameObjectAttatchedTo, TRANSFORM_COMPONENT);
        Vector2* movement = ICM_InputControllerGet_NormalizedMovement(input);
        Vector2* result = CreateVector2(0, 0);
        MultiplyVector2ByScalar(movement, controller->base.speed, result);
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
    }
}

#endif //DEFAULT_SHIP_MOVEMENT_CONTROLLER_C