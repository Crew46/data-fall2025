#ifndef COMPONENT_MANAGER_C
#define COMPONENT_MANAGER_C
#include "component_manager.h"
#include "../object/object_manager.h"
#include "update_components_dispatcher.c"
#include "construct_components_dispatcher.c"

ComponentManager* componentManager;

//=========================================================
///////////////////////////////////////////////////////////
///////////MANAGER INITIALIZATION//////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void CM_Initialize()
{
    componentManager = (ComponentManager*)malloc(sizeof(ComponentManager));
    componentManager->list = ConstructDoublyLinkedList();
    componentManager->nextComponentID = 0;
}

void CM_Deinitialize(ComponentManager* componentManager)
{
}

//=========================================================
///////////////////////////////////////////////////////////
///////////COMPONENT FUNCTIONS/////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void CM_InitializeComponent(Component* component, ComponentType type)
{
    //initialize base object through object manager
    OM_InitializeObject((Object*)component);
    //initialize component
    component->CID = componentManager->nextComponentID;
    componentManager->nextComponentID++;
    component->type = type;
    //not attached to gameobject when created  
    component->gameObjectAttatchedTo = NULL;
    DoublyLinkedListInsertElementToTail(componentManager->list, (Object*)component);
}

Component* CM_ConstructComponent(ComponentType type)
{
    return DispatchComponentConstructionFunction(type);
}

void CM_DeconstructComponent(Component* component)
{
    //remove from component list
    RemoveElementFromDoublyLinkedList(componentManager->list, (Object*)component);
    //dispatch destruct function to component systems
    //
    //
    free(component);
}

void CM_UpdateComponent(Component* component)
{
    //if active, update component
    if(component && CM_ComponentGet_IsActive(component))
    {
        DispatchComponentsUpdateFunction(component);
    }
}

//=========================================================
///////////////////////////////////////////////////////////
///////////GETTERS AND SETTERS/////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

//======//
//OBJECT//
//======//

//set name
void CM_ComponentSet_Name(Component* component, int* name)
{
    OM_ObjectSet_Name((Object*)component, name);
}
//get name
int* CM_ComponentGet_Name(Component* component)
{
    return OM_ObjectGet_Name((Object*)component);
}
//set isactive
void CM_ComponentSet_IsActive(Component* component, bool isActive)
{
    OM_ObjectSet_IsActive((Object*)component, isActive);
}
//get isactive
bool CM_ComponentGet_IsActive(Component* component)
{
    return OM_ObjectGet_IsActive((Object*)component);
}
//get underlying objectid
int CM_ComponentGet_ObjectID(Component* component)
{
    return OM_ObjectGet_OID((Object*)component);
}

//=========//
//COMPONENT//
//=========//

//set GameObjectAttatchedTo
void CM_ComponentSet_GameObjectAttatchedTo(Component* component, GameObject* gameObjectAttatchedTo)
{
    component->gameObjectAttatchedTo = gameObjectAttatchedTo;
}
//get GameObjectAttatchedTo
GameObject* CM_ComponentGet_GameObjectAttatchedTo(Component* component)
{
    return component->gameObjectAttatchedTo;
}
//set ComponentType
void CM_ComponentSet_ComponentType(Component* component, ComponentType type)
{
    component->type = type;
}
//get ComponentType
ComponentType CM_ComponentGet_ComponentType(Component* component)
{
    return component->type;
}
//set Component ID
void CM_ComponentSet_CID(Component* component, int CID)
{
    component->CID = CID;
}
//Get Component ID
int CM_ComponentGet_CID(Component* component)
{
    return component->CID;
}

//=======//
//MANAGER//
//=======//

ComponentManager* CM_GetComponentManager()
{
    return componentManager;
}

#endif // COMPONENT_MANAGER_C