#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H
#include "component.h"
#include "../data_structures/doubly_linked_list/doubly_linked_list.h"

DoublyLinkedList* componentList = CreateDoublyLinkedList();

int nextComponentID = 0; //keeps track of the next compoent ID to assign

void ComponentManagerInitializeComponent(Component* component, int* name, ComponentType type)
{
    InitializeComponent(component, name, type, nextObjectID);
    nextComponentID++;
    DoublyLinkedListInsertAtTail(componentList, (Object*)component);
}

Component* ComponentManagerCreateComponent(int* name, ComponentType type)
{
    //create and initialize object
    Component* component = (Component*)malloc(sizeof(Component));
    ComponentManagerInitializeComponent(component, name, type);
    //return object
    return component;
}

void ComponentManagerDeconstructComponent(Component* component)
{
    //remove from list
    //deconstuct
    DeconstructComponent(component);
}

#endif //COMPONENT_MANAGER_H