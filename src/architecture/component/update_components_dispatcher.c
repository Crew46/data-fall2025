#ifndef UPDATE_COMPONENTS_DISPATCHER_C
#define UPDATE_COMPONENTS_DISPATCHER_C
#include "component.h"
#include "../../systems/transform/transform_manager.h"
#include "../../systems/rendering/render_manager.h"
#include "../../systems/player/player_controller_manager.h"
#include "../../systems/physics/collider/collider_manager.h"

void DispatchComponentsUpdateFunction(Component* component)
{
    switch(component->type)
    {
        case PLAYER_CONTROLLER_COMPONENT:
            UpdatePlayerController((PlayerController*)component);
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
            //call weapon controller update function
            break;
        default:
            break;
    }
}

#endif // UPDATE_COMPONENTS_DISPATCHER_C