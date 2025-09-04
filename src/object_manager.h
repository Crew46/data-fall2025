#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H
#include "object.h"
#include "data_structures/doubly_linked_list/doubly_linked_list.h"

DoublyLinkedList* objectList = CreateDoublyLinkedList();

int nextObjectID = 0; //keeps track of the next object ID to assign

void ObjectManagerInitializeObject(Object* object, int* name)
{
    InitializeObject(object, name, nextObjectID);
    nextObjectID++;
}

Object* ObjectManagerCreateObject(int* name)
{
    Object* object = (Object*)malloc(sizeof(Object));
    ObjectManagerInitializeObject(object, name);
    return object;
}

void ObjectManagerDeconstructObject(Object* object)
{
    DeconstructObject(object);
}

#endif //OBJECT_MANAGER_H