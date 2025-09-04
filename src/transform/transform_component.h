#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H
#include "../component_based_architecture/component/component_manager.h"
#include "../vector/vector2.h"

struct TransformComponent
{
    Component base; //base component
    Vector2 position; //position in scene
};

void InitializeTransformComponent(TransformComponent* transformComponent, int* name)
{
    //initialize component base
    ComponentManagerInitializeComponent(transformComponent->base, name, TRANSFORM_COMPONENT);
    //initialize vector to 0, 0
    InitializeVector2(transformComponent->position, 0, 0);
}

void DeconstructTransformComponent(TransformComponent* transform)
{
    //deconstuct component
    ComponentManagerDeconstructComponent(transform->base);
    //position
    DeconstructVector2(transform->position); 
    free(transform);
}

#endif // RENDER_COMPONENT_H