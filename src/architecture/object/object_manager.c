#ifndef OBJECT_MANAGER_C
#define OBJECT_MANAGER_C
#include "object_manager.h"

void InitializeObjectManager(ObjectManager* objectManager)
{
    objectManager->objectList = CreateDoublyLinkedList();
    objectManager->nextObjectID = 0;
}

ObjectManager* ConstructObjectManager()
{
    ObjectManager* objectManager = (ObjectManager*)malloc(sizeof(ObjectManager));
    InitializeObjectManager(objectManager);
    return objectManager;
}

void DeconstructObjectManager(ObjectManager* objectManager)
{
    //deconstruct all objects in list
    //here//
    //free object manager struct
    free(objectManager);
}

void ObjectManagerInitializeObject(ObjectManager* objectManager, Object* object)
{
    int* name = "unnamed";
    //copy the string that was passed in into the player name field
    int* playerName = (int*)malloc(sizeof(int) * (strlen(name) + 1));
    strcpy(playerName, name); 
    object->name = playerName;
    object->isActive = true;
    object->objectID = objectManager->nextObjectID;
    objectManager->nextObjectID++;
    DoublyLinkedListInsertAtTail(objectManager->objectList, object);
}

Object* ObjectManagerConstructObject(ObjectManager* objectManager)
{
    Object* object = (Object*)malloc(sizeof(Object));
    ObjectManagerInitializeObject(objectManager, object);
    return object;
}

void ObjectManagerDeconstructObject(ObjectManager* ObjectManager, Object* object)
{
    //remove from linked list

    //deconstruct
    free(object->name);
    free(object);
}

#endif // OBJECT_MANAGER_C