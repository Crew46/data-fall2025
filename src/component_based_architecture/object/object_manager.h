#ifndef OBJECCT_MANAGER_H
#define OBJECT_MANAGER_H
#include "object.h"
#include "../../data_structures/doubly_linked_list/doubly_linked_list.h"

int nextObjectID = 0; //keeps track of the next object ID to assign

DoublyLinkedList* objectList = CreateDoublyLinkedList(); //OBJECT LINKED LIST

void ObjectManagerInitializeObject(Object* object, int* name)
{
    InitializeObject(object, name, nextObjectID);
    nextObjectID++;
    DoublyLinkedListInsertAtTail(objectList, object);
}

Object* ObjectManagerConstructObject(int* name)
{
    Object* object = (Object*)malloc(sizeof(Object));
    ObjectManagerInitializeObject(object, name);
    return object;
}

void ObjectManagerDeconstructObject(Object* object)
{
    //remove from linked list

    //deconstruct
    DeconstructObject(object);
}
#endif // OBJECT_MANAGER_H