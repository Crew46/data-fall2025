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
void OM_Initialize();
void OM_Deinitialize();
//object creation
void OM_InitializeObject(Object* object);
Object* OM_ConstructObject();
void OM_DeconstructObject(Object* object);

//=========================================================
///////////////////////////////////////////////////////////
///////////GETTERS AND SETTERS/////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

//======//
//OBJECT//
//======//

void OM_ObjectSet_Name(Object* object, int* name);
int* OM_ObjectGet_Name(Object* object);

void OM_ObjectSet_IsActive(Object* object, bool isActive);
bool OM_ObjectGet_IsActive(Object* object);

void OM_ObjectSet_OID(Object* object, int OID);
int OM_ObjectGet_OID(Object* object);

//=======//
//MANAGER//
//=======//

ObjectManager* OM_GetObjectManager();

#endif // OBJECT_MANAGER_H