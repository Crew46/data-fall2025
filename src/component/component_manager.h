#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H
#include "component.h"
#include "../data_structures/doubly_linked_list/doubly_linked_list.h"

DoublyLinkedList* objectList = CreateDoublyLinkedList();

int nextObjectID = 0; //keeps track of the next object ID to assign

void ComponentManagerInitializeComponent(Component* object, int* name)
{
    InitializeComponent(object, name, nextObjectID);
    nextObjectID++;
    DoublyLinkedListInsertAtTail(objectList, object);
}

Component* ComponentManagerCreateComponent(int* name)
{
    //create and initialize object
    Component* object = (Component*)malloc(sizeof(Component));
    ComponentManagerInitializeComponent(object, name);
    //return object
    return object;
}

void ComponentManagerDeconstructComponent(Component* object)
{
    DeconstructComponent(object);
}

#endif //OBJECT_MANAGER_H