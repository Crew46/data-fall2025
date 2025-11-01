#ifndef UPDATE_COMPONENTS_DISPATCHER_C
#define UPDATE_COMPONENTS_DISPATCHER_C
#include "component.h"
#include "../../systems/transform/transform_manager.h"
#include "../../systems/rendering/render_manager.h"
#include "../../systems/ship/ship_controller_manager.h"
#include "../../systems/physics/collider/collider_manager.h"
#include "../../systems/input/input_controller_manager.h"
#include "../../systems/health/health_controller_manager.h"
#include "../../systems/weapon/weapon/weapon_controller_manager.h"

void DispatchComponentsUpdateFunction(Component* component)
{
    switch(component->type)
    {
        case SHIP_CONTROLLER_COMPONENT:
            UpdateShipController((ShipController*)component);
            break;
        case TRANSFORM_COMPONENT:
            UpdateTransformComponent((TransformComponent*)component); 
            break;
        case RENDER_COMPONENT:
            UpdateRenderComponent((RenderComponent*)component);
            break;
        case RIGIDBODY_COMPONENT:
            //call rigidbody update function
            break;
        case COLLIDER_COMPONENT:
            UpdateCollider((Collider*)component); 
            break;
        case WEAPON_CONTROLLER_COMPONENT:
            WCM_WeaponController_Update((WeaponController*)component);
            break;
        case INPUT_CONTROLLER_COMPONENT:
            ICM_UpdateInputController((InputController*)component);
            break;
        case HEALTH_CONTROLLER_COMPONENT:
            UpdateHealthController((HealthController*)component);
            break;
        default:
            break;
    }
}

#endif // UPDATE_COMPONENTS_DISPATCHER_C