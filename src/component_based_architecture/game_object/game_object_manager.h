#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H
#include "game_object.h"
#include "../component/component_manager.h"
#include "../../data_structures/doubly_linked_list/doubly_linked_list.h"

int nextGameObjectID = 0; //keeps track of the next gameObject ID to assign

DoublyLinkedList* gameObjectList = CreateDoublyLinkedList(); //game object list

void GameObjectManagerInitializeGameObject(GameObject* gameObject, int* name)
{
    InitializeGameObject(gameObject, name, nextGameObjectID);
    nextGameObjectID++;
    DoublyLinkedListInsertAtTail(gameObjectList, (Object*)gameObject);
}

GameObject* GameObjectManagerConstructGameObject(int* name)
{
    GameObject* gameObject = (GameObject*)malloc(sizeof(GameObject));
    GameObjectManagerInitializeGameObject(gameObject, name);
    return gameObject;
}

//=========================================================
///////////////////////////////////////////////////////////
///////////Game Object Functions///////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

//find the game object that a component belongs to
GameObject* GetGameObjectOfComponent(Component* component)
{
    DoublyNode* currentGameObjectNode = gameObjectList->head;
    GameObject* currentGameObject = NULL;

    DoublyNode* currentComponentNode = ((GameObject*)currentGameObjectNode->data)->components->head;
    Component* currentComponent = NULL;

    //loop through all game objects
    while(currentGameObjectNode != NULL)
    {
        //set current game object to next element
        currentGameObject = (GameObject*)currentGameObjectNode->data;

        if(currentGameObject != NULL)
        {
            //loop through children list
            while(currentComponentNode != NULL)
            {
                //set current component to next element in list
                currentComponent = (Component*)currentComponentNode->data;

                //if component matches, return game object
                if(currentComponent == component)
                {
                    return currentGameObject;
                }

                //move to next component in list
                currentComponentNode = currentComponentNode->next;
            }
        }

        //move to next game object in list
        currentGameObjectNode = currentGameObjectNode->next;
    }
    return NULL;
}

//get component of a specific type from a game object
Component* GameObjectGetComponentByType(GameObject* gameObject, ComponentType type)
{
    DoublyNode* currentComponentNode = gameObject->children->head;
    GameObject* currentComponent = NULL;

    while(currentComponentNode != NULL)
    {
        currentComponent = (Component*)currentComponentNode->data;
        if(currentComponent->type == type)
        {
            return currentComponent;
        }
        currentComponentNode = currentComponentNode->next;
    }
    return NULL;
}

//find a component of a specific type, given a component that belongs to the same game object
Component* GetComponentFromComponent(Component* component, ComponentType type)
{
    GameObject* gameObject = GetGameObjectOfComponent(component);
    if(gameObject != NULL)
    {
        return GameObjectManagerGetGamemanagerComponentByType(gameObject, type);
    }
    return NULL;
}

void UpdateAllGameObjects()
{
    DoublyNode* currentNode = gameObjectList->head;
    GameObject* currentGameObject = NULL;

    //loop through all game objects
    while(currentNode != NULL)
    {
        //set current game object to next element in list
        currentGameObject = (GameObject*)currentNode->data;

        GameObjectUpdate(currentGameObject);

        //move to next game object in list
        currentNode = currentNode->next;
    }
}


#endif //GAME_OBJECT_MANAGER_H