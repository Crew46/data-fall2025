#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H
#include "component.h"
#include "../data_structures/doubly_linked_list/doubly_linked_list.h"

DoublyLinkedList* componentList = CreateDoublyLinkedList();

int nextComponentID = 0; //keeps track of the next compoent ID to assign

void ComponentManagerInitializeComponent(Component* component, int* name, ComponentType type)
{
    InitializeComponent(component, name, type, nextObjectID);
    nextComponentID++;
    DoublyLinkedListInsertAtTail(componentList, (Object*)component);
}

Component* ComponentManagerConstructComponent(int* name, ComponentType type)
{
    //create and initialize object
    Component* component = (Component*)malloc(sizeof(Component));
    ComponentManagerInitializeComponent(component, name, type);
    //return object
    return component;
}

void ComponentManagerDeconstructComponent(Component* component)
{
    //remove from list
    //deconstuct
    DeconstructComponent(component);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////UPDATE ALL COMPONENTS///////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void UpdateAllComponents()
{
    DoublyNode* currentNode = componentList->head;
    Component* currentComponent = NULL;

    //loop through all components
    while(currentNode != NULL)
    {
        //set current component to next element in list
        currentComponent = (Component*)currentNode->data;

        //update component
        UpdateComponent(currentComponent);

        //move to next component in list
        currentNode = currentNode->next;
    }
}


#endif //COMPONENT_MANAGER_H