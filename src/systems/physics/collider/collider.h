#ifndef COLLIDER_H
#define COLLIDER_H
#include "../../../architecture/component/component.h"

enum ColliderShape
{
    RECTANGLE,
    CIRCLE,
};

struct Collider
{
    Component base;
    ColliderShape shape;
    Vector2 dimensions; // For RECTANGLE and CIRCLE shapes
    bool isColliding;
};

#endif // COLLIDER_H
