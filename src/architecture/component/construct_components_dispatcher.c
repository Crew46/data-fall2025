#ifndef CONSTRUCT_COMPONENTS_DISPATCHER_C
#define CONSTRUCT_COMPONENTS_DISPATCHER_C
#include "component.h"
#include "../../systems/transform/transform_manager.h"
#include "../../systems/rendering/render_manager.h"
#include "../../systems/player/player_manager.h"
#include "../../systems/physics/collider/collider_manager.h"

Component* DispatchComponentConstructionFunction(ComponentType type)
{
    Component* componentToReturn = NULL;
    switch(type)
    {
        case PLAYER_CONTROLLER_COMPONENT:
            componentToReturn = (Component*)ConstructPlayerController();
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
        case WEAPON_CONTROLLER_COMPONENT:
            //construct weapon controller component
            break;
        default:
            break;
    }
    return componentToReturn;
}

#endif // CONSTRUCT_COMPONENTS_DISPATCHER_C