#ifndef OBJECT_H
#define OBJECT_H
#include "misc.h"

struct Object
{
    int* name; //string for name of object
    bool isActive; //active in scene
    int objectID;
};

#endif // OBJECT_H