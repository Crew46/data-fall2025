#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H
#include "../../architecture/component/component.h"
#include "../../vector/vector2.h"

struct TransformComponent
{
    Component base; //base component
    Vector2 position; //position in scene
    Vector2 localPosition; //local position relative to parent
    float rotation; //about origin; clockwise in radians
    float localRotation; //about parent; clockwise in radians
};

#endif // RENDER_COMPONENT_H