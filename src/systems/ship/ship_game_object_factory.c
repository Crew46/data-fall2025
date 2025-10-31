#ifndef SHIP_GAMEOBJECT_FACTORY_C
#define SHIP_GAMEOBJECT_FACTORY_C
#include "../../architecture/game_object/game_object_manager.h"
#include "../input/input_controller_manager.h"
#include "../ship/ship_controller_manager.h"
#include "../transform/transform_manager.h"
#include "../health/health_controller_manager.h"
#include "../rendering/render_manager.h"

GameObject* CreateShipGameObject(int* name, int gamePad, InputControllerType type, int region, int texture, int x, int y)
{
    GameObject* ship = GOM_ConstructGameObject();
    TransformComponent* transform = (TransformComponent*)GOM_AddComponentToGameObject(ship, TRANSFORM_COMPONENT);
    RenderComponent* renderComponent = (RenderComponent*)GOM_AddComponentToGameObject(ship, RENDER_COMPONENT);
    ShipController* shipController = (ShipController*)GOM_AddComponentToGameObject(ship, SHIP_CONTROLLER_COMPONENT);
    InputController* inputController = (InputController*)GOM_AddComponentToGameObject(ship, INPUT_CONTROLLER_COMPONENT);
    HealthController* healthController = (HealthController*)GOM_AddComponentToGameObject(ship, HEALTH_CONTROLLER_COMPONENT);
    
    GOM_GameObjectSet_Name(ship, name);

    //set gamepad of player controller component
    ICM_InputControllerSet_Gamepad(inputController, 0);
    ICM_InputControllerSet_Type(inputController, type);

    //set the region and texture of the render component
    SetRenderComponentRegion(renderComponent, PLAYER_REGION);
    SetRenderComponentTexture(renderComponent, PLAYER_SPRITES_TEXTURE);
    //set position of the transform
    TransformComponentSetGlobalPosition(transform, x, y);

}

#endif //SHIP_GAMEOBJECT_FACTORY_C
