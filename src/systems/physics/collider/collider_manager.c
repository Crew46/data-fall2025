#ifndef COLLIDER_MANAGER_C
#define COLLIDER_MANAGER_C
#include "collider_manager.h"
#include "../../../data_structures/doubly_linked_list/doubly_linked_list.h"

ColliderManager* colliderManager;

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

}

PlayerController* ConstructCollider()
{

}

void DeconstructCollider(Collider* collider)
{

}

void UpdateCollider(Collider* collider)
{
    print_at(screen_width / 2, screen_height / 2 + 150, "updating collider");
}

#endif //COLLIDER_MANAGER_C