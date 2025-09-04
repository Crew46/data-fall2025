#ifndef OBJECT_H
#define OBJECT_H
#include "string.h"
#include "../vector/vector2.h"

////////////////////////////////////////////////////////////////
///////////Struct///////////////////////////////////////////////
////////////////////////////////////////////////////////////////

struct Component
{
    int* name; //string for name of object
    Vector2 position; //position in scene
    int id; //object id
    bool isActive; //active in scene
};

////////////////////////////////////////////////////////////////
///////////Constructor & Deconstructor//////////////////////////
////////////////////////////////////////////////////////////////

void InitializeObject(Component* object, int* name, int id)
{
    //copy the string that was passed in into the player name field
    int* playerName = (int*)malloc(sizeof(int) * (strlen(name) + 1));
    strcpy(playerName, name); 

    //initialize fields given in parameters
    object->name = playerName;
    object->id = id;

    //initialize garbage values
    object->isActive = true; //default to active
    object->position.x = 0;
    object->position.y = 0;
}

Component* CreateObject(int* name, int id)
{
    //allocate object
    Component* object = (Component*)malloc(sizeof(Component));
    //initialize object
    InitializeObject(object, name, id);
    //return object
    return object;
}

//string needs to be freed alongside the entire object, because object owns the string
void DeconstructObject(Component* object)
{
    //free string
    free(object->name);
    //free struct
    free(object);
}

#endif //OBJECT_H