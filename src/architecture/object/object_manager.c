#ifndef OBJECT_MANAGER_C
#define OBJECT_MANAGER_C
#include "object_manager.h"

ObjectManager* objectManager;

//=========================================================
///////////////////////////////////////////////////////////
//////////MANAGER INITIALIZATION///////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

ObjectManager* GetObjectManager()
{
    return objectManager;
}

void InitializeObjectManager()
{
    objectManager = (ObjectManager*)malloc(sizeof(ObjectManager));
    objectManager->objectList = ConstructDoublyLinkedList();
    objectManager->nextObjectID = 0;
}

void DeinitializeObjectManager()
{
    //deconstruct all objects in list
    //here//
    //free object manager struct
    free(objectManager);
}

//=========================================================
///////////////////////////////////////////////////////////
//////////OBJECT CONSTRUCTION AND INITIALIZATION///////////
///////////////////////////////////////////////////////////
//=========================================================

void InitializeObject(Object* object)
{
    SetObjectName(object, "unamed");
    object->isActive = true;
    object->objectID = objectManager->nextObjectID;
    objectManager->nextObjectID++;
    DoublyLinkedListInsertToTail(objectManager->objectList, object);
}

Object* ConstructObject()
{
    Object* object = (Object*)malloc(sizeof(Object));
    InitializeObject(object);
    return object;
}

void DeconstructObject(Object* object)
{
    //remove from linked list

    //deconstruct
    free(object->name);
    free(object);
}

//=========================================================
///////////////////////////////////////////////////////////
/////////GETTERS & SETTERS/////////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void SetObjectName(Object* object, int* name)
{
    int* playerName = (int*)malloc(sizeof(int) * (strlen(name) + 1));
    strcpy(playerName, name);
    object->name = playerName;
}

#endif // OBJECT_MANAGER_C