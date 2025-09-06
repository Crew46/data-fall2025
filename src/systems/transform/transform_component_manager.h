#ifndef TRANSFORM_COMPONENT_MANAGER_H
#define TRANSFORM_COMPONENT_MANAGER_H
#include "../../architecture/component/component_manager_declaration.h"
#include "../../vector/vector2.h"

//=========================================================
///////////////////////////////////////////////////////////
/////////////CONSTRUCTION & DECONSTRUCTION/////////////////
///////////////////////////////////////////////////////////
//=========================================================

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

#endif // TRANSFORM_COMPONENT_MANAGER_H