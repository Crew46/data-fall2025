#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H
#include "component.h"
#include "../data_structures/doubly_linked_list/doubly_linked_list.h"

DoublyLinkedList* objectList = CreateDoublyLinkedList();

int nextObjectID = 0; //keeps track of the next object ID to assign

void ObjectManagerInitializeObject(Component* object, int* name)
{
    InitializeObject(object, name, nextObjectID);
    nextObjectID++;
    DoublyLinkedListInsertAtTail(objectList, object);
}

Component* ObjectManagerCreateObject(int* name)
{
    //create and initialize object
    Component* object = (Component*)malloc(sizeof(Component));
    ObjectManagerInitializeObject(object, name);
    //return object
    return object;
}

void ObjectManagerDeconstructObject(Component* object)
{
    DeconstructObject(object);
}

#endif //OBJECT_MANAGER_H