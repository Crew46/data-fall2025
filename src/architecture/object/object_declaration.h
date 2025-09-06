#ifndef OBJECT_DECLARATION_H
#define OBJECT_DECLARATION_H
#include "misc.h"

struct Object
{
    int* name; //string for name of object
    bool isActive; //active in scene
    int objectID;
};

#endif // OBJECT_DECLARATION_H