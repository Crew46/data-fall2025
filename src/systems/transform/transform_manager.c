#ifndef TRANSFORM_MANAGER_C
#define TRANSFORM_MANAGER_C
#include "transform_manager.h"
#include "../../architecture/component/component_manager.h"
#include "../../architecture/game_object/game_object_manager.h"
#include "../../architecture/object/object_manager.h"

//=========================================================
///////////////////////////////////////////////////////////
/////////////COMPONENT CONSTRUCTION & INITIALIZATION///////
///////////////////////////////////////////////////////////
//=========================================================

//transform components

void InitializeTransformComponent(TransformComponent* transformComponent)
{
    //initialize component base
    CM_InitializeComponent((Component*)transformComponent, TRANSFORM_COMPONENT);
    OM_ObjectSet_Name((Object*)transformComponent, "Transform_Component");
    //initialize vector to 0, 0
    InitializeVector2(&transformComponent->position, 0, 0);
    InitializeVector2(&transformComponent->localPosition, 0, 0);
    transformComponent->localRotation = 0;
    transformComponent->rotation = 0;
}

TransformComponent* ConstructTransformComponent()
{
    //allocate memory
    TransformComponent* transformComponent = (TransformComponent*)malloc(sizeof(TransformComponent));
    //initialize
    InitializeTransformComponent(transformComponent);
    return transformComponent;
}

void DeconstructTransformComponent(TransformComponent* transform)
{
    //deconstuct component
    CM_DeconstructComponent(&transform->base);
    //position
    DeconstructVector2(&transform->position); 
    DeconstructVector2(&transform->localPosition);
    //free struct
    free(transform);
}

//=========================================================
///////////////////////////////////////////////////////////
/////////////BEHAVIOURAL FUNCTIONS/////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void UpdateTransformComponent(TransformComponent* transformComponent)
{
    if(transformComponent != NULL)
    {
    }
}
// transform component functions

Vector2* CalculateGlobalPosition(TransformComponent* transformComponent)
{
    //calculate global position based on local position and parent's position
}

Vector2* CalculateLocalPosition(TransformComponent* transformComponent)
{
}

Vector2* CalculateLocalRotation(TransformComponent* transformComponent)
{
    //calculate local rotation based on parent's rotation
}

//=========================================================
///////////////////////////////////////////////////////////
/////////////GETTERS & SETTERS/////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void TransformComponentSetGlobalPosition(TransformComponent* transformComponent, int x, int y)
{
    transformComponent->position.x = x;
    transformComponent->position.y = y;
    //if parent is not root, calculate and set local position
    //if parent is root, local and globa position are equal
}

void TransformComponentSetLocalPosition(TransformComponent* transformComponent, int x, int y)
{
    //if parent is not root, set local position
    transformComponent->localPosition.x = x;
    transformComponent->localPosition.y = y;
    //if parent is root, local position is global position
}


#endif // TRANSFORM_MANAGER_C