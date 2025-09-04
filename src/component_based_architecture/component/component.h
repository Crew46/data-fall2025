#ifndef COMPONENT_H
#define COMPONENT_H
#include "../object/object_manager.h"

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
    int componentID; //object id
};

void InitializeComponent(Component* component, int* name, ComponentType type, int componentID)
{
    //initialize base object through object manager
    ObjectManagerInitializeObject(&component->base, name);
    //initialize component
    component->componentID = componentID;
    component->type = type;
}

//string needs to be freed alongside the entire object, because object owns the string
void DeconstructComponent(Component* component)
{
    //tell object manager to deconstuct object
    ObjectManagerDeconstructObject(&component->base);
    //free struct
    free(component);
}

#endif //COMPONENT_H