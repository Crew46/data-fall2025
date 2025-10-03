#ifndef COLLIDER_MANAGER_H
#define COLLIDER_MANAGER_H
#include "../../../data_structures/doubly_linked_list/doubly_linked_list.h"
#include "collider.h"
#include "../../../vector/vector2.h"

struct ColliderManager
{
    DoublyLinkedList* colliderList;
};

void InitializeColliderManager();
void DeinitializeColliderManager();


//collider instance functions
void InitializeCollider(Collider* collider);
Collider* ConstructCollider();
void DeconstructCollider(Collider* collider);
void UpdateCollider(Collider* collider);
ColliderManager* GetColliderManager();

//getters and settes
bool GetIsColliderColliding(Collider* collider);
void SetColliderDimensions(Collider* collider, int x, int y);
void SetColliderShape(Collider* collider, ColliderShape shape);


bool CheckIfPointInBoundsOfCollider(Vector2* point, Collider* collider);
void ColliderUpdateIfCollision(Collider* collider);
bool ColliderCalculateIfRectangleCollision(Collider* collider);
bool ColliderCalculateIfCircleCollision(Collider* collider);

#endif //COLLIDER_MANAGER_H