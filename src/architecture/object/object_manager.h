#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H
#include "../object/object.h"
#include "../../data_structures/doubly_linked_list/doubly_linked_list.h"

struct ObjectManager
{
    DoublyLinkedList* objectList; //list of objects
    int nextObjectID; //keeps track of the next object ID to assign
};

//manager initialization
void InitializeObjectManager();
void DeinitializeObjectManager();
//object creation
void InitializeObject(Object* object);
Object* ConstructObject();
void DeconstructObject(Object* object);
//getters and setters
void SetObjectName(Object* object, int* name);
ObjectManager* GetObjectManager();

#endif // OBJECT_MANAGER_H