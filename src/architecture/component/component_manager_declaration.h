#ifndef COMPONENT_MANAGER_DECLARATION_H
#define COMPONENT_MANAGER_DECLARATION_H
#include "../component/component_declaration.h"
#include "../../data_structures/doubly_linked_list/doubly_linked_list_declaration.h"
#include "../object/object_manager_declaration.h"

struct ComponentManager
{
    DoublyLinkedList* componentList; //list of components
    int nextComponentID; //keeps track of the next compoent ID to assign
    ObjectManager* objectManager; //reference to object manager
};

void InitializeComponentManager(ComponentManager* componentManager, ObjectManager* objectManager);
ComponentManager* ConstructComponentManager(ObjectManager* objectManager);
void DeconstructComponentManager(ComponentManager* componentManager);
void ComponentManagerInitializeComponent(ComponentManager* componentManager, Component* component, int* name, ComponentType type);
Component* ComponentManagerConstructComponent(ComponentManager* componentManager, int* name, ComponentType type);
void ComponentManagerDeconstructComponent(ComponentManager* componentManager, Component* component);
void UpdateComponent(Component* component);

#endif // COMPONENT_MANAGER_DECLARATION_H