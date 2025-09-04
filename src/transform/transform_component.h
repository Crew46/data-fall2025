#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H
#include "../component/component.h"

struct TransformComponent
{
    Component component; //base component
    Vector2 position; //position in scene
};

#endif // RENDER_COMPONENT_H