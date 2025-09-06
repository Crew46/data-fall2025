#ifndef COMPONENT_MANAGERS_CONTAINER_H
#define COMPONENT_MANAGERS_CONTAINER_H
#include "../../systems/transform/transform_manager.h"

struct ComponentManagersContainer
{
    TransformManager* transformManager; //reference to transform manager
};

#endif // COMPONENT_MANAGERS_CONTAINER_H