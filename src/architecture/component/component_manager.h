#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H
#include "../component/component.h"
#include "../../data_structures/doubly_linked_list/doubly_linked_list.h"
#include "../game_object/game_object.h"

struct ComponentManager
{
    DoublyLinkedList* componentList; //list of components
    int nextComponentID; //keeps track of the next compoent ID to assign
};

//manager initialization
void InitializeComponentManager();
void DeinitializeComponentManager(ComponentManager* componentManager);
//manager getters & setters
ComponentManager* GetComponentManager();


//component construction & initialization
void ComponentManagerInitializeComponent(Component* component, ComponentType type);
Component* ComponentManagerConstructComponent(ComponentType type);
void ComponentManagerDeconstructComponent(Component* component);

//functions
void ComponentManagerUpdateComponent(Component* component);

//component getters & setters
void ComponentManagerSetGameObjectOfComponent(Component* component, GameObject* gameObject);

#endif // COMPONENT_MANAGER_H