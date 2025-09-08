#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H
#include "../component/component.h"
#include "../../data_structures/doubly_linked_list/doubly_linked_list.h"
#include "../object/object_manager.h"

struct ComponentManager
{
    DoublyLinkedList* componentList; //list of components
    int nextComponentID; //keeps track of the next compoent ID to assign
    ObjectManager* objectManager; //reference to object manager
};

void InitializeComponentManager(ComponentManager* componentManager, ObjectManager* objectManager);
ComponentManager* ConstructComponentManager(ObjectManager* objectManager);
void DeconstructComponentManager(ComponentManager* componentManager);
void ComponentManagerInitializeComponent(ComponentManager* componentManager, Component* component, ComponentType type);
Component* ComponentManagerConstructComponent(ComponentManager* componentManager, ComponentType type);
void ComponentManagerDeconstructComponent(ComponentManager* componentManager, Component* component);
void UpdateComponent(Component* component);

#endif // COMPONENT_MANAGER_H