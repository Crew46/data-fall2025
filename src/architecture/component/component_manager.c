#ifndef COMPONENT_MANAGER_C
#define COMPONENT_MANAGER_C
#include "component_manager.h"
#include "../object/object_manager.h"
#include "update_components_dispatcher.c"
#include "construct_components_dispatcher.c"

ComponentManager* componentManager;

ComponentManager* GetComponentManager()
{
    return componentManager;
}

//=========================================================
///////////////////////////////////////////////////////////
///////////MANAGER INITIALIZATION//////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void InitializeComponentManager()
{
    componentManager = (ComponentManager*)malloc(sizeof(ComponentManager));
    componentManager->componentList = ConstructDoublyLinkedList();
    componentManager->nextComponentID = 0;
}

void DeinitializeComponentManager(ComponentManager* componentManager)
{
    //deconstruct all components in list
    //here//
    //free component manager struct
    free(componentManager);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////COMPONENT CONSTRUCTION & DECONSTRUCTION/////////
///////////////////////////////////////////////////////////
//=========================================================

void InitializeComponent(Component* component, ComponentType type)
{
    //initialize base object through object manager
    InitializeObject(&component->base);
    //initialize component
    component->componentID = componentManager->nextComponentID;
    componentManager->nextComponentID++;
    component->type = type;
    //not attached to gameobject when created  
    component->gameObject = NULL;
    DoublyLinkedListInsertToTail(componentManager->componentList, ConstructDoublyNode((Object*)component));
}

Component* ConstructComponent(ComponentType type)
{
    return DispatchComponentConstructionFunction(type);
}

void DeconstructComponent(Component* component)
{
    //remove from list
    //deconstuct
    //tell object manager to deconstuct object
    DeconstructObject(&component->base);
    //free struct
    free(component);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////UPDATE ALL COMPONENTS///////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void UpdateComponent(Component* component)
{
    //if active, update component
    if(&component->base.isActive)
    {
        DispatchComponentsUpdateFunction(component);
    }
}

//=========================================================
///////////////////////////////////////////////////////////
///////////GETTERS & SETTERS///////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void SetGameObjectOfComponent(Component* component, GameObject* gameObject)
{
    component->gameObject = gameObject;
}
#endif // COMPONENT_MANAGER_C