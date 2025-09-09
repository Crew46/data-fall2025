#ifndef TRANSFORM_MANAGER_C
#define TRANSFORM_MANAGER_C
#include "transform_manager.h"
#include "../../architecture/component/component_manager.h"
#include "../../architecture/game_object/game_object_manager.h"

TransformManager* transformManager;

TransformManager* GetTransformManager()
{
    return transformManager;
}

//=========================================================
///////////////////////////////////////////////////////////
/////////////CONSTRUCTION & DECONSTRUCTION/////////////////
///////////////////////////////////////////////////////////
//=========================================================

void InitializeTransformManager()
{
    //allocate memory
    transformManager = (TransformManager*)malloc(sizeof(TransformManager));
    //initialize
    transformManager->transformComponents = CreateDoublyLinkedList();
}

//deconstruct transform manager
void DeinitializeTransformManager(TransformManager* transformManager)
{
    //free linked list
    ///////////////
    free(transformManager);
}

void InitializeTransformComponent(TransformComponent* transformComponent)
{
    //initialize component base
    ComponentManagerInitializeComponent(&transformComponent->base, TRANSFORM_COMPONENT);
    //initialize vector to 0, 0
    InitializeVector2(&transformComponent->position, 0, 0);
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
    ComponentManagerDeconstructComponent(&transform->base);
    //position
    DeconstructVector2(&transform->position); 
    free(transform);
}

void UpdateTransformComponent(TransformComponent* transformComponent)
{
    print_at(transformComponent->position.x, transformComponent->position.y, "*&*");
    //update transform component
}
// transform component functions

void TransformComponentSetGlobalPosition(TransformComponent* transformComponent, int x, int y)
{
    transformComponent->position.x = x;
    transformComponent->position.y = y;
}

void TransformComponentSetLocalPosition(TransformComponent* transformComponent, int x, int y)
{
}

//=========================================================
///////////////////////////////////////////////////////////
/////////////LOCAL ROTATION AND POSITION///////////////////
///////////////////////////////////////////////////////////
//=========================================================

Vector2* CalculateGlobalPosition(TransformComponent* transformComponent)
{
    //calculate global position based on local position and parent's position
}

Vector2* CalculateLocalPosition(TransformComponent* transformComponent)
{
    //calculate local position based on parent's position
    GameObject* parentGameObject = GetGameObjectOfComponent((Component*)transformComponent);
    if(parentGameObject != NULL)
    {
       TransformComponent* parentTransform = (TransformComponent*)GameObjectGetComponentByType(parentGameObject, TRANSFORM_COMPONENT); 
    }
}

Vector2* CalculateLocalRotation(TransformComponent* transformComponent)
{
    //calculate local rotation based on parent's rotation
}

#endif // TRANSFORM_MANAGER_C