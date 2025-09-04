#ifndef OBJECT_H
#define OBJECT_H
#include "misc.h"

struct Object
{
    int* name; //string for name of object
    bool isActive; //active in scene
    int objectID;
};

void InitializeObject(Object* object, int* name, int objectID)
{
    //copy the string that was passed in into the player name field
    int* playerName = (int*)malloc(sizeof(int) * (strlen(name) + 1));
    strcpy(playerName, name); 
    object->name = playerName;
    object->isActive = true;
    object->objectID = objectID;
}

void DeconstructObject(Object* object)
{
    free(object->name);
    free(object);
}

#endif // GAME_OBJECT_H