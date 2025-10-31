#ifndef COMPONENT_H
#define COMPONENT_H
#include "../object/object.h"
#include "../game_object/game_object.h"

enum ComponentType
{
    TRANSFORM_COMPONENT,
    RENDER_COMPONENT,
    RIGIDBODY_COMPONENT,
    COLLIDER_COMPONENT,
    SHIP_CONTROLLER_COMPONENT,
    WEAPON_CONTROLLER_COMPONENT,
    INPUT_CONTROLLER_COMPONENT,
    HEALTH_CONTROLLER_COMPONENT
};

struct Component
{
    Object base; //base object
    GameObject* gameObjectAttatchedTo; //reference to gameobject of this component
    ComponentType type; //type of component
    int CID; //component id
};

#endif // COMPONENT_H