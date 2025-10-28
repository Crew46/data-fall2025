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
}

//=========================================================
///////////////////////////////////////////////////////////
///////////COMPONENT CONSTRUCTION & DECONSTRUCTION/////////
///////////////////////////////////////////////////////////
//=========================================================

void ComponentManagerInitializeComponent(Component* component, ComponentType type)
{
    //initialize base object through object manager
    ObjectManagerInitializeObject((Object*)component);
    //initialize component
    component->componentID = componentManager->nextComponentID;
    componentManager->nextComponentID++;
    component->type = type;
    //not attached to gameobject when created  
    component->gameObject = NULL;
    DoublyLinkedListInsertElementToTail(componentManager->componentList, (Object*)component);
}

Component* ComponentManagerConstructComponent(ComponentType type)
{
    return DispatchComponentConstructionFunction(type);
}

void ComponentManagerDeconstructComponent(Component* component)
{
    ObjectManagerDeconstructObject((Object*)component);
    //free struct
    free(component);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////UPDATE ALL COMPONENTS///////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void ComponentManagerUpdateComponent(Component* component)
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

void ComponentManagerSetGameObjectOfComponent(Component* component, GameObject* gameObject)
{
    component->gameObject = gameObject;
}
#endif // COMPONENT_MANAGER_C