#ifndef UPDATE_COMPONENTS_DISPATCHER_C
#define UPDATE_COMPONENTS_DISPATCHER_C
#include "component.h"

void DispatchUpdateFunctionToComponents(Component* component)
{
    switch(component->type)
    {
        case PLAYER_CONTROLLER_COMPONENT:
            //call player controller update function
            break;
        case TRANSFORM_COMPONENT:
            //call transform update function
            break;
        case RENDER_COMPONENT:
            //call render update function
            break;
        case RIGIDBODY_COMPONENT:
            //call rigidbody update function
            break;
        case COLLIDER_COMPONENT:
            //call collider update function
            break;
        case WEAPON_CONTROLLER_COMPONENT:
            //call weapon controller update function
            break;
        default:
            break;
    }
}

#endif // UPDATE_COMPONENTS_DISPATCHER_C