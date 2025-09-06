#ifndef TRANSFORM_MANAGER_H
#define TRANSFORM_MANAGER_H
#include "../../architecture/component/component_manager.h"
#include "../../vector/vector2.h"
#include "../../data_structures/doubly_linked_list/doubly_linked_list.h"
#include "transform_component.h"

struct TransformManager
{
    DoublyLinkedList* transformComponents; //list of all transform components
    ComponentManager* componentManager; //reference to component manager
};

TransformManager* ConstructTransformManager(ComponentManager* componentManager);
void DeconstructTransformManager(TransformManager* transformManager);
void InitializeTransformComponent(TransformManager* transformManager, TransformComponent* transformComponent, int* name);
TransformComponent* ConstructTransformComponent(TransformManager* transformManager, int* name);
void DeconstructTransformComponent(TransformManager* transformManager, TransformComponent* transform);
void UpdateTransformComponent(TransformComponent* transformComponent);
void UpdateAllTransformComponents(TransformManager* transformManager);

#endif //TRANSFORM_MANAGER_H