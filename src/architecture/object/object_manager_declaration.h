#ifndef OBJECT_MANAGER_DECLARATION_H
#define OBJECT_MANAGER_DECLARATION_H
#include "../object/object_declaration.h"
#include "../../data_structures/doubly_linked_list/doubly_linked_list_declaration.h"

struct ObjectManager
{
    DoublyLinkedList* objectList; //list of objects
    int nextObjectID; //keeps track of the next object ID to assign
};

void InitializeObjectManager(ObjectManager* objectManager);
ObjectManager* ConstructObjectManager();
void DeconstructObjectManager(ObjectManager* objectManager);
void ObjectManagerInitializeObject(ObjectManager* objectManager, Object* object, int* name);
Object* ObjectManagerConstructObject(ObjectManager* objectManager, int* name);
void ObjectManagerDeconstructObject(ObjectManager* ObjectManager, Object* object);

#endif // OBJECT_MANAGER_DECLARATION_H