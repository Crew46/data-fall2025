#ifndef TRANSFORM_MANAGER_C
#define TRANSFORM_MANAGER_C
#include "transform_manager.h"
#include "../../architecture/component/component_manager.h"

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
    print_at(screen_width / 2, screen_height / 2, "Updating Transform Component");
    //update transform component
}

void UpdateAllTransformComponents()
{
    DoublyNode* currentNode = transformManager->transformComponents->head;
    TransformComponent* currentData = NULL;
    while(currentNode != NULL)
    {
        currentData = (TransformComponent*)currentNode->data;
        if(currentData != NULL)
        {
            UpdateTransformComponent((TransformComponent*)currentData);
        }
        currentNode = currentNode->next;
    }
}

#endif // TRANSFORM_MANAGER_C