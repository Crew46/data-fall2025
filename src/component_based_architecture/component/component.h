#ifndef COMPONENT_H
#define COMPONENT_H
#include "string.h"
#include "../vector/vector2.h"
#include "../object/object_manager.h"

////////////////////////////////////////////////////////////////
///////////Struct///////////////////////////////////////////////
////////////////////////////////////////////////////////////////

//this enum will be used to identify component types

enum ComponentType
{
    TRANSFORM_COMPONENT,
    RENDER_COMPONENT,
    RIGIDBODY_COMPONENT,
    COLLIDER_COMPONENT
};

struct Component
{
    Object base; //base object
    ComponentType type; //type of component
    int componentID; //object id
};

////////////////////////////////////////////////////////////////
///////////Constructor & Deconstructor//////////////////////////
////////////////////////////////////////////////////////////////

void InitializeComponent(Component* component, int* name, ComponentType type, int componentID)
{
    //initialize base object through object manager
    ObjectManagerInitializeObject(&component->object, name);
    //initialize component
    component->componentID = componentID;
    component->type = type;
}

//string needs to be freed alongside the entire object, because object owns the string
void DeconstructComponent(Component* component)
{
    //tell object manager to deconstuct object
    ObjectManagerDeconstructObject(component->object);
    //free struct
    free(component);
}

#endif //COMPONENT_H