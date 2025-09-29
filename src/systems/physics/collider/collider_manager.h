#ifndef COLLIDER_MANAGER_H
#define COLLIDER_MANAGER_H
#include "../../../data_structures/doubly_linked_list/doubly_linked_list.h"
#include "collider.h"

struct ColliderManager
{
    DoublyLinkedList* colliderList;
};

void InitializeColliderManager();
void DeinitializeColliderManager();
void InitializeCollider(Collider* collider);
PlayerController* ConstructCollider();
void DeconstructCollider(Collider* collider);
void UpdateCollider(Collider* collider);

#endif //COLLIDER_MANAGER_H