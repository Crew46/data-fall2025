#ifndef CONSTRUCT_COMPONENTS_DISPATCHER_C
#define CONSTRUCT_COMPONENTS_DISPATCHER_C
#include "component.h"
#include "../../systems/transform/transform_manager.h"

void DispatchConstructionFunctionToComponentManager(int* name, ComponentType type)
{
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
}

void InitializeConstructComponentsDispatcher()
{

}

#endif // CONSTRUCT_COMPONENTS_DISPATCHER_C