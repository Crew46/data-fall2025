#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "../component/component_manager.h"
#include "../object/object_manager.h"   
#include "../../data_structures/doubly_linked_list/doubly_linked_list.h"

struct GameObject
{
    Object base; //base object
    DoublyLinkedList* children; //list of children
    int gameObjectID;
};

GameObject* InitializeGameObject(GameObject* gameObject, int* name, int gameObjectID)
{
    //initialize base object through object manager
    ObjectManagerInitializeObject(gameObject->base, name);
    //initialize gameobject
    gameObject->gameObjectID = gameObjectID;
    //initialize linked list
    children = CreateDoublyLinkedList();
}

void DeconstructGameObject(GameObject* gameObject)
{
    //deconstruct object through object manager
    ObjectManagerDeconstructObject(gameObject->base);
    //deconstuct all children of linked list
    //here//

    //free game object
    free(gameObject);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////Game Object Functions///////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void GameObjectAddComponent(GameObject* gameObject, Component* component)
{
    //add component to linked list of components
    DoublyLinkedListInsertAtTail(gameObject->components, (Object*)component);
}

void GameObjectUpdate(GameObject* gameObject)
{
    DoublyNode* currentComponentNode = gameObject->children->head;
    Component* currentComponent = NULL;
    //if game object not null & is active
    if(currentGameObject != NULL && currentGameObject->base->isActive)
    {
        while(currentComponentNode != NULL)
        {
            currentComponent = (Component*)currentComponentNode->data;

            //update component
            UpdateComponent(currentComponent);

            //move to next component in list
            currentComponentNode = currentComponentNode->next;
        }
    }
}


#endif // GAME_OBJECT_H