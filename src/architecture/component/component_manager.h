#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H
#include "../component/component.h"
#include "../../data_structures/doubly_linked_list/doubly_linked_list.h"

struct ComponentManager
{
    DoublyLinkedList* componentList; //list of components
    int nextComponentID; //keeps track of the next compoent ID to assign
};

void InitializeComponentManager();
void DeinitializeComponentManager(ComponentManager* componentManager);
void ComponentManagerInitializeComponent(Component* component, ComponentType type);
Component* ComponentManagerConstructComponent(ComponentType type);
void ComponentManagerDeconstructComponent(Component* component);
void UpdateComponent(Component* component);
ComponentManager* GetComponentManager();

#endif // COMPONENT_MANAGER_H