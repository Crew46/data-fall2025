#ifndef SHIP_GAMEOBJECT_FACTORY_C
#define SHIP_GAMEOBJECT_FACTORY_C
#include "../../architecture/game_object/game_object_manager.h"
#include "../input/input_controller_manager.h"
#include "../ship/ship_controller_manager.h"
#include "../transform/transform_manager.h"
#include "../health/health_controller_manager.h"
#include "../rendering/render_manager.h"

GameObject* CreateShipGameObject(int* name, int x, int y, int region, int texture, int drawPriority, int gamePad, InputControllerType inputType, int maxHealth, int maxGraceTime, ShipType shipType, int speed)
{
    GameObject* ship = GOM_ConstructGameObject();
    TransformComponent* transform = (TransformComponent*)GOM_AddComponentToGameObject(ship, TRANSFORM_COMPONENT);
    RenderComponent* renderComponent = (RenderComponent*)GOM_AddComponentToGameObject(ship, RENDER_COMPONENT);
    InputController* inputController = (InputController*)GOM_AddComponentToGameObject(ship, INPUT_CONTROLLER_COMPONENT);
    HealthController* healthController = (HealthController*)GOM_AddComponentToGameObject(ship, HEALTH_CONTROLLER_COMPONENT);
    ShipController* shipController = (ShipController*)GOM_AddComponentToGameObject(ship, SHIP_CONTROLLER_COMPONENT);
    
    GOM_GameObjectSet_Name(ship, name);

    TransformComponentSet_DescriptiveData(transform, x, y);
    SetRenderComponentDescriptiveData(renderComponent, region, texture, drawPriority);
    ICM_InputControllerSet_DescriptiveData(inputController, inputType, gamePad);
    HealthControllerSet_DescriptiveData(healthController, maxHealth, maxGraceTime);
    ShipControllerSet_DescriptiveData(shipController, shipType, speed);
}

#endif //SHIP_GAMEOBJECT_FACTORY_C
