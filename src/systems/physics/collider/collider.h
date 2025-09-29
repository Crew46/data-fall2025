#ifndef COLLIDER_H
#define COLLIDER_H
#include "../../../architecture/component/component.h"

enum ColliderShape
{
    RECTANGLE,
    CIRCLE,
    POLYGON
};

struct Collider
{
    Component base;
    ColliderShape shape;
    Vector2 boundTopLeft;
    Vector2 boundBottomRight;
};

#endif // COLLIDER_H
