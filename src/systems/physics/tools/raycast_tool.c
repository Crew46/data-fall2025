#ifndef RAYCAST_TOOL_C
#define RAYCAST_TOOL_C
#include "raycast_tool.h"
#include "../collider/collider_manager.h"
#include "../../transform/transform_manager.h"
#include "../../../architecture/game_object/game_object_manager.h"
#include "math.h"

DoublyLinkedList* CastRay(Vector2* vector, Vector2* origin)
{
    DoublyNode* currentNode = GetColliderManager()->colliderList->head;      
    Collider* currentCollider = NULL;
    TransformComponent* currentTransform = NULL; 
    while(currentNode != NULL)
    {
        currentCollider = (Collider*)currentNode->data;
        currentTransform = (TransformComponent*)GetComponentFromComponent((Component*)currentCollider, TRANSFORM_COMPONENT);
        if(currentCollider != NULL && currentTransform != NULL)
        {
            float possibleYCollisionPoint = currentTransform->position.x * (vector->y/vector->x) + origin->y;
            Vector2* pointOfPossibleCollision = CreateVector2(currentTransform->position.x, possibleYCollisionPoint);
            CheckIfPointInBoundsOfCollider(pointOfPossibleCollision, currentCollider);
        }
        currentNode = currentNode->next;
    }
}

#endif //RAYCAST_TOOL_C