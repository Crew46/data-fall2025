#ifndef CONSTRUCT_COMPONENTS_DISPATCHER_C
#define CONSTRUCT_COMPONENTS_DISPATCHER_C
#include "component.h"
#include "../../systems/transform/transform_manager.h"
#include "../../systems/rendering/render_manager.h"
#include "../../systems/ship/ship_controller_manager.h"
#include "../../systems/physics/collider/collider_manager.h"
#include "../../systems/input/input_controller_manager.h"
#include "../../systems/health/health_controller_manager.h"
#include "../../systems/weapon/weapon/weapon_controller_manager.h"

Component* DispatchComponentConstructionFunction(ComponentType type)
{
    Component* componentToReturn = NULL;
    switch(type)
    {
        case SHIP_CONTROLLER_COMPONENT:
            componentToReturn = (Component*)ConstructShipController();
            break;
        case TRANSFORM_COMPONENT:
            componentToReturn = (Component*)ConstructTransformComponent();
            break;
        case RENDER_COMPONENT:
            componentToReturn = (Component*)ConstructRenderComponent();
            break;
        case RIGIDBODY_COMPONENT:
            //construct rigidbody component
            break;
        case COLLIDER_COMPONENT:
            componentToReturn = (Component*)ConstructCollider();
            break;
        case INPUT_CONTROLLER_COMPONENT:
            componentToReturn = (Component*)ICM_ConstructInputController();
            break;
        case WEAPON_CONTROLLER_COMPONENT:
            componentToReturn = (Component*)WCM_WeaponControllerConstruct();
            break;
        case HEALTH_CONTROLLER_COMPONENT:
            componentToReturn = (Component*)ConstructHealthController();
            break;
        default:
            break;
    }
    return componentToReturn;
}

#endif // CONSTRUCT_COMPONENTS_DISPATCHER_C