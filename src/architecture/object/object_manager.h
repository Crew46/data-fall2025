#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H
#include "../object/object.h"
#include "../../data_structures/doubly_linked_list/doubly_linked_list.h"

struct ObjectManager
{
    DoublyLinkedList* objectList; //list of objects
    int nextObjectID; //keeps track of the next object ID to assign
};

void InitializeObjectManager(ObjectManager* objectManager);
ObjectManager* ConstructObjectManager();
void DeconstructObjectManager(ObjectManager* objectManager);
void ObjectManagerInitializeObject(ObjectManager* objectManager, Object* object);
Object* ObjectManagerConstructObject(ObjectManager* objectManager);
void ObjectManagerDeconstructObject(ObjectManager* ObjectManager, Object* object);

#endif // OBJECT_MANAGER_H