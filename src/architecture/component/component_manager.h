#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H
#include "../component/component.h"
#include "../../data_structures/doubly_linked_list/doubly_linked_list.h"
#include "../game_object/game_object.h"

/*
    Component Manager (CM) API:
*/

struct ComponentManager
{
    DoublyLinkedList* list; //list of components
    int nextComponentID; //keeps track of the next compoent ID to assign
};

//=========================================================
///////////////////////////////////////////////////////////
///////////MANAGER FUNCTIONS///////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

//manager initialization
void CM_Initialize();
void CM_Deinitialize(ComponentManager* componentManager);

//=========================================================
///////////////////////////////////////////////////////////
///////////COMPONENT FUNCTIONS/////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

//component construction & initialization
void CM_InitializeComponent(Component* component, ComponentType type);
Component* CM_ConstructComponent(ComponentType type);
void CM_DeconstructComponent(Component* component);

//functions
void CM_UpdateComponent(Component* component);


//=========================================================
///////////////////////////////////////////////////////////
///////////GETTERS AND SETTERS/////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

//////////
//OBJECT//
//////////

//name
void CM_ComponentSet_Name(Component* component, int* name);
int* CM_ComponentGet_Name(Component* component);
//isactive
void CM_ComponentSet_IsActive(Component* component, bool isActive);
bool CM_ComponentGet_IsActive(Component* component);
//objectid
int CM_ComponentGet_ObjectID(Component* component);

/////////////
//COMPONENT//
/////////////

//GameObjectAttatchedTo
void CM_ComponentSet_GameObjectAttatchedTo(Component* component, GameObject* gameObjectAttatchedTo);
GameObject* CM_ComponentGet_GameObjectAttatchedTo(Component* component);
//ComponentType
void CM_ComponentSet_ComponentType(Component* component, ComponentType type);
ComponentType CM_ComponentGet_ComponentType(Component* component);
//Component ID
int CM_ComponentGet_CID(Component* component);
void CM_ComponentSet_CID(Component* component, int CID);

///////////
//MANAGER//
///////////

ComponentManager* CM_GetComponentManager();

#endif // COMPONENT_MANAGER_H