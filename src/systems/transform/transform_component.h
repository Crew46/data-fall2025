#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H
#include "../../architecture/component/component_manager_declaration.h"
#include "../../vector/vector2.h"

struct TransformComponent
{
    Component base; //base component
    Vector2 position; //position in scene
};

#endif // RENDER_COMPONENT_H