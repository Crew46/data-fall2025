#ifndef OBJECT_MANAGER_C
#define OBJECT_MANAGER_C
#include "object_manager.h"

ObjectManager* objectManager;

//=========================================================
///////////////////////////////////////////////////////////
//////////MANAGER INITIALIZATION///////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void OM_Initialize()
{
    objectManager = (ObjectManager*)malloc(sizeof(ObjectManager));
    objectManager->objectList = ConstructDoublyLinkedList();
    objectManager->nextObjectID = 0;
}

void OM_Deinitialize()
{
    //deconstruct all objects in list
    //here//
    //free object manager struct
    free(objectManager);
}

//=========================================================
///////////////////////////////////////////////////////////
//////////OBJECT //////////////////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void OM_InitializeObject(Object* object)
{
    object->name = NULL;
    object->isActive = true;
    object->OID = objectManager->nextObjectID;
    objectManager->nextObjectID++;
    OM_ObjectSet_Name(object, "unamed");
    DoublyLinkedListInsertElementToTail(objectManager->objectList, object);
}

Object* OM_ConstructObject()
{
    Object* object = (Object*)malloc(sizeof(Object));
    OM_InitializeObject(object);
    return object;
}

void OM_DeconstructObject(Object* object)
{
    //remove from linked list

    //deconstruct
    free(object->name);
    free(object);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////GETTERS AND SETTERS/////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

//======//
//OBJECT//
//======//

void OM_ObjectSet_Name(Object* object, int* name)
{
    int* playerName = (int*)malloc(sizeof(int) * (strlen(name) + 1));
    strcpy(playerName, name);

    if(object->name)
    {
       free(object->name);
    }

    object->name = playerName;
}
int* OM_ObjectGet_Name(Object* object)
{
    return object->name;
}

void OM_ObjectSet_IsActive(Object* object, bool isActive)
{
    object->isActive = isActive;
}
bool OM_ObjectGet_IsActive(Object* object)
{
    return object->isActive;
}

void OM_ObjectSet_OID(Object* object, int OID)
{
    object->OID = OID;
}
int OM_ObjectGet_OID(Object* object)
{
    return object->OID;
}

//=======//
//MANAGER//
//=======//

ObjectManager* OM_GetObjectManager()
{
    return objectManager;
}

#endif // OBJECT_MANAGER_C