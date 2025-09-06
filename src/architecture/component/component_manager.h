#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H
#include "component_manager_declaration.h"

//=========================================================
///////////////////////////////////////////////////////////
///COMPONENT MANAGER CONSTRUCTION & DECONSTRUCTION/////////
///////////////////////////////////////////////////////////
//=========================================================

void InitializeComponentManager(ComponentManager* componentManager, ObjectManager* objectManager)
{
    componentManager->componentList = CreateDoublyLinkedList();
    componentManager->nextComponentID = 0;
    componentManager->objectManager = objectManager;
}

ComponentManager* ConstructComponentManager(ObjectManager* objectManager)
{
    ComponentManager* componentManager = (ComponentManager*)malloc(sizeof(ComponentManager));
    InitializeComponentManager(componentManager, objectManager);
    return componentManager;
}

void DeconstructComponentManager(ComponentManager* componentManager)
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

void ComponentManagerInitializeComponent(ComponentManager* componentManager, Component* component, int* name, ComponentType type)
{
    //initialize base object through object manager
    ObjectManagerInitializeObject(componentManager->objectManager, &component->base, name);
    //initialize component
    component->componentID = componentManager->nextComponentID;
    component->type = type;
    componentManager->nextComponentID++;
    DoublyLinkedListInsertAtTail(componentManager->componentList, (Object*)component);
}

Component* ComponentManagerConstructComponent(ComponentManager* componentManager, int* name, ComponentType type)
{
    //create and initialize object
    Component* component = (Component*)malloc(sizeof(Component));
    ComponentManagerInitializeComponent(componentManager, component, name, type);
    //return object
    return component;
}

void ComponentManagerDeconstructComponent(ComponentManager* componentManager, Component* component)
{
    //remove from list
    //deconstuct
    //tell object manager to deconstuct object
    ObjectManagerDeconstructObject(componentManager->objectManager, &component->base);
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
    //update component
}

#endif // COMPONENT_MANAGER_H