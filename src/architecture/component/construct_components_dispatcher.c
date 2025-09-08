#ifndef CONSTRUCT_COMPONENTS_DISPATCHER_C
#define CONSTRUCT_COMPONENTS_DISPATCHER_C
#include "component.h"

Component* DispatchComponentConstructionFunction(ComponentType type)
{
    Component* componentToReturn = NULL;
    switch(type)
    {
        case PLAYER_CONTROLLER_COMPONENT:
            //construct player controller component
            break;
        case TRANSFORM_COMPONENT:
            break;
        case RENDER_COMPONENT:
            //construct render component
            break;
        case RIGIDBODY_COMPONENT:
            //construct rigidbody component
            break;
        case COLLIDER_COMPONENT:
            //construct collider component
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