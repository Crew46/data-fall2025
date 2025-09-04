#ifndef COMPONENT_H
#define COMPONENT_H
#include "string.h"
#include "../vector/vector2.h"

////////////////////////////////////////////////////////////////
///////////Struct///////////////////////////////////////////////
////////////////////////////////////////////////////////////////

struct Component
{
    int* name; //string for name of object
    int id; //object id
    bool isActive; //active in scene
};

////////////////////////////////////////////////////////////////
///////////Constructor & Deconstructor//////////////////////////
////////////////////////////////////////////////////////////////

void InitializeComponent(Component* component, int* name, int id)
{
    //copy the string that was passed in into the player name field
    int* playerName = (int*)malloc(sizeof(int) * (strlen(name) + 1));
    strcpy(playerName, name); 

    //initialize fields given in parameters
    component->name = playerName;
    component->id = id;

    //initialize garbage values
    component->isActive = true; //default to active
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