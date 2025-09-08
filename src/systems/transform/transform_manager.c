#ifndef TRANSFORM_MANAGER_C
#define TRANSFORM_MANAGER_C
#include "transform_manager.h"
#include "video.h"

//=========================================================
///////////////////////////////////////////////////////////
/////////////CONSTRUCTION & DECONSTRUCTION/////////////////
///////////////////////////////////////////////////////////
//=========================================================

TransformManager* ConstructTransformManager(ComponentManager* componentManager)
{
    //allocate memory
    TransformManager* transformManager = (TransformManager*)malloc(sizeof(TransformManager));
    //initialize
    transformManager->transformComponents = CreateDoublyLinkedList();
    transformManager->componentManager = componentManager;
    return transformManager;
}

//deconstruct transform manager
void DeconstructTransformManager(TransformManager* transformManager)
{
    //free linked list
    ///////////////
    free(transformManager);
}

void InitializeTransformComponent(TransformManager* transformManager, TransformComponent* transformComponent)
{
    //initialize component base
    ComponentManagerInitializeComponent(&transformComponent->base, TRANSFORM_COMPONENT);
    //initialize vector to 0, 0
    InitializeVector2(&transformComponent->position, 0, 0);
}

TransformComponent* ConstructTransformComponent(TransformManager* transformManager)
{
    //allocate memory
    TransformComponent* transformComponent = (TransformComponent*)malloc(sizeof(TransformComponent));
    //initialize
    InitializeTransformComponent(transformManager, transformComponent);
    return transformComponent;
}

void DeconstructTransformComponent(TransformManager* transformManager, TransformComponent* transform)
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

void UpdateAllTransformComponents(TransformManager* transformManager)
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