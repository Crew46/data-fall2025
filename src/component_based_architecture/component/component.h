#ifndef COMPONENT_H
#define COMPONENT_H
#include "string.h"
#include "../vector/vector2.h"
#include "../object/object.h"

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

void InitializeComponent(Component* component, ComponentType type, int componentID)
{
    //allocate component
    Component* component = (Component*)malloc(sizeof(Component));
    //initialize base object through object manager

    //initialize component
    componentID = componentID;

    //return component
    return component;
}

Component* CreateComponent(int* name, int id)
{
    //allocate object
    Component* component = (Component*)malloc(sizeof(Component));
    //initialize object
    InitializeComponent(component, name, id);
    //return object
    return component;
}

//string needs to be freed alongside the entire object, because object owns the string
void DeconstructComponent(Component* component)
{
    //free string
    free(component->name);
    //free struct
    free(component);
}

#endif //COMPONENT_H