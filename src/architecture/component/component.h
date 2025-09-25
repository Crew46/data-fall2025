#ifndef COMPONENT_H
#define COMPONENT_H
#include "../object/object.h"
#include "../game_object.h"

enum ComponentType
{
    TRANSFORM_COMPONENT,
    RENDER_COMPONENT,
    RIGIDBODY_COMPONENT,
    COLLIDER_COMPONENT,
    PLAYER_CONTROLLER_COMPONENT,
    WEAPON_CONTROLLER_COMPONENT
};

struct Component
{
    Object base; //base object
    ComponentType type; //type of component
    int componentID; //component id
};

#endif // COMPONENT_H