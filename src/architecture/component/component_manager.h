#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H
#include "../component/component.h"
#include "../../data_structures/doubly_linked_list/doubly_linked_list.h"

struct ComponentManager
{
    DoublyLinkedList* componentList; //list of components
    int nextComponentID; //keeps track of the next compoent ID to assign
};

//manager initialization
void InitializeComponentManager();
void DeinitializeComponentManager(ComponentManager* componentManager);
//component construction
void InitializeComponent(Component* component, ComponentType type);
Component* ConstructComponent(ComponentType type);
void DeconstructComponent(Component* component);
//functions
void UpdateComponent(Component* component);
ComponentManager* GetComponentManager();

#endif // COMPONENT_MANAGER_H