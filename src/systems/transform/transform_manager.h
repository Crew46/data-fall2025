#ifndef TRANSFORM_MANAGER_H
#define TRANSFORM_MANAGER_H
#include "transform_component.h"
#include "../../data_structures/doubly_linked_list/doubly_linked_list.h"

struct TransformManager
{
    DoublyLinkedList* transformComponents; //list of all transform components
};

void InitializeTransformManager();
void DeinitializeTransformManager(TransformManager* transformManager);
void InitializeTransformComponent(TransformComponent* transformComponent);
TransformComponent* ConstructTransformComponent();
void DeconstructTransformComponent(TransformComponent* transform);
void UpdateTransformComponent(TransformComponent* transformComponent);
void UpdateAllTransformComponents();
TransformManager* GetTransformManager();

#endif //TRANSFORM_MANAGER_H