#ifndef COLLIDER_MANAGER_C
#define COLLIDER_MANAGER_C
#include "collider_manager.h"
#include "../../../data_structures/doubly_linked_list/doubly_linked_list.h"
#include "../../../architecture/component/component_manager.c"
#include "math.h"
#include "../../../architecture/game_object/game_object_manager.h"
#include "../../transform/transform_manager.h"

ColliderManager* colliderManager;

ColliderManager* GetColliderManager()
{
    return colliderManager;
}

void InitializeColliderManager()
{
    colliderManager = (ColliderManager*)malloc(sizeof(ColliderManager));
    colliderManager->colliderList = ConstructDoublyLinkedList();
}

void DeinitializeColliderManager()
{
    //free doubly linked list
    free(colliderManager);
}

void InitializeCollider(Collider* collider)
{
    CM_InitializeComponent((Component*)collider, COLLIDER_COMPONENT);
    collider->shape = RECTANGLE;
    collider->dimensions.x = 50;
    collider->dimensions.y = 50;
}

Collider* ConstructCollider()
{
    Collider* collider = (Collider*)malloc(sizeof(Collider));
    InitializeCollider(collider);
    DoublyLinkedListInsertElementToTail(colliderManager->colliderList, (Object*)collider);
    return collider;
}

void DeconstructCollider(Collider* collider)
{
    //free base
    CM_DeconstructComponent((Component*)collider);
    free(collider);
}

void UpdateCollider(Collider* collider)
{
    print_at(screen_width / 2, screen_height / 2 + 150, "updating collider");
    ColliderUpdateIfCollision(collider);
}

bool CheckIfPointInBoundsOfCircle(Vector2* point, Collider* collider)
{

}

bool CheckIfPointInBoundsOfRectangle(Vector2* point, Collider* collider)
{
    TransformComponent* transform = (TransformComponent*)GOM_GetComponentFromComponent((Component*)collider, TRANSFORM_COMPONENT);
    if(transform != NULL && collider != NULL)
    {
        float lengthFromCenterToHorizontalEdge = collider->dimensions.x / 2;
        float lengthFromCenterToVerticalEdge = collider->dimensions.y / 2;
        //if in domain and range of rectangle hitbox
        if(point->x >= (transform->position.x - lengthFromCenterToHorizontalEdge))
        {
            if(point->x <= (transform->position.x + lengthFromCenterToHorizontalEdge))
            {
                if(point->y >= (transform->position.y - lengthFromCenterToVerticalEdge))
                {
                    if(point->y <= (transform->position.y + lengthFromCenterToHorizontalEdge))
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool CheckIfPointInBoundsOfCollider(Vector2* point, Collider* collider)
{
    bool result = false;
    //determine if in bounds, based on the shape of the collider
    switch (collider->shape)
    {
    case RECTANGLE:
        result = CheckIfPointInBoundsOfRectangle(point, collider);
        break;
    case CIRCLE:
        result = CheckIfPointInBoundsOfCircle(point, collider);
        break;
    default:
        break;
    }
    return result;
}

void ColliderUpdateIfCollision(Collider* collider)
{
    bool result = false;
    if(collider->shape == RECTANGLE)
    {
        result = ColliderCalculateIfRectangleCollision(collider);
    }
    else if(collider->shape == CIRCLE)
    {
        result = ColliderCalculateIfCircleCollision(collider);
    }
    collider->isColliding = result;
}

bool ColliderCalculateIfRectangleCollision(Collider* collider)
{
    TransformComponent* transformComponent = (TransformComponent*)GOM_GetComponentFromComponent((Component*)collider, TRANSFORM_COMPONENT);
    TransformComponent* otherTransformComponent = NULL;
    Collider* otherColliderComponent = NULL;

    //return if component to check's tranform is NULL
    if(transformComponent == NULL)
    {
        return false;
    }

    DoublyNode* currentNode = colliderManager->colliderList->head;
    Collider* data = NULL;

    while(currentNode != NULL)
    {
        data = (Collider*)currentNode->data;
        otherTransformComponent = (TransformComponent*)GOM_GetComponentFromComponent((Component*)data, TRANSFORM_COMPONENT);
        otherColliderComponent = (Collider*)GOM_GetComponentFromComponent((Component*)data, COLLIDER_COMPONENT);

        //if current gameobject's transform & collider components exist
        if(otherTransformComponent != NULL && otherColliderComponent != NULL)
        {
        }
        currentNode = currentNode->next;
    }
}

bool ColliderCalculateIfCircleCollision(Collider* collider)
{

}

bool GetIsColliderColliding(Collider* collider)
{
    return collider->isColliding;
}

void SetColliderDimensions(Collider* collider, int x, int y)
{
    collider->dimensions.x = x;
    collider->dimensions.y = y;
}

void SetColliderShape(Collider* collider, ColliderShape shape)
{
    collider->shape = shape;
}

#endif //COLLIDER_MANAGER_C