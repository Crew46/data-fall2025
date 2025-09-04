#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H
#include "component.h"
#include "../data_structures/doubly_linked_list/doubly_linked_list.h"

DoublyLinkedList* componentList = CreateDoublyLinkedList();

int nextObjectID = 0; //keeps track of the next object ID to assign

void ComponentManagerInitializeComponent(Component* component, int* name)
{
    InitializeComponent(component, name, nextObjectID);
    nextObjectID++;
    DoublyLinkedListInsertAtTail(componentList, component);
}

Component* ComponentManagerCreateComponent(int* name)
{
    //create and initialize object
    Component* component = (Component*)malloc(sizeof(Component));
    ComponentManagerInitializeComponent(component, name);
    //return object
    return component;
}

void ComponentManagerDeconstructComponent(Component* component)
{
    DeconstructComponent(component);
}

#endif //COMPONENT_MANAGER_H