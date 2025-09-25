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
///COMPONENT MANAGER CONSTRUCTION & DECONSTRUCTION/////////
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

void ComponentManagerInitializeComponent(Component* component, ComponentType type)
{
    //initialize base object through object manager
    ObjectManagerInitializeObject(&component->base);
    //initialize component
    component->componentID = componentManager->nextComponentID;
    componentManager->nextComponentID++;
    component->type = type;
    DoublyLinkedListInsertToTail(componentManager->componentList, (Object*)component);
}

Component* ComponentManagerConstructComponent(ComponentType type)
{
    return DispatchComponentConstructionFunction(type);
}

void ComponentManagerDeconstructComponent(Component* component)
{
    //remove from list
    //deconstuct
    //tell object manager to deconstuct object
    ObjectManagerDeconstructObject(&component->base);
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
    if(&component->base.isActive)
    {
        DispatchComponentsUpdateFunction(component);
    }
}

#endif // COMPONENT_MANAGER_C