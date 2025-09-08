#ifndef OBJECT_MANAGER_C
#define OBJECT_MANAGER_C
#include "object_manager.h"

ObjectManager* objectManager;

ObjectManager* GetObjectManager()
{
    return objectManager;
}

void InitializeObjectManager()
{
    objectManager = (ObjectManager*)malloc(sizeof(ObjectManager));
    objectManager->objectList = CreateDoublyLinkedList();
    objectManager->nextObjectID = 0;
}

void DeinitializeObjectManager()
{
    //deconstruct all objects in list
    //here//
    //free object manager struct
    free(objectManager);
}

void ObjectManagerInitializeObject(Object* object)
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

Object* ObjectManagerConstructObject()
{
    Object* object = (Object*)malloc(sizeof(Object));
    ObjectManagerInitializeObject(object);
    return object;
}

void ObjectManagerDeconstructObject(Object* object)
{
    //remove from linked list

    //deconstruct
    free(object->name);
    free(object);
}

void ObjectManagerSetObjectName(Object* object, int* name)
{
    int* playerName = (int*)malloc(sizeof(int) * (strlen(name) + 1));
    strcpy(playerName, name);
    object->name = playerName;
}

#endif // OBJECT_MANAGER_C