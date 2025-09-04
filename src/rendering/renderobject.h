#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H
#include "object.h"

struct RenderObject
{
    Component object; //base object
    int textureID; //texture id
    int regionID; //region id
}

#endif // RENDEROBJECT_H