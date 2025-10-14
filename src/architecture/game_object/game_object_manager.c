#ifndef GAME_OBJECT_MANAGER_C
#define GAME_OBJECT_MANAGER_C
#include "game_object_manager.h"
#include "../component/component_manager.h"
#include "../object/object_manager.h"
#include "../../data_structures/doubly_linked_list/doubly_linked_list.h"

//declarations
GameObjectManager* gameObjectManager;

GameObjectManager* GetGameObjectManager()
{
    return gameObjectManager;
}

GameObject* GetRootGameObject()
{
    return gameObjectManager->root;
}

//=========================================================
///////////////////////////////////////////////////////////
///////////MANAGER INITILIZATION///////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void InitializeGameObjectManager()
{
    gameObjectManager = (GameObjectManager*)malloc(sizeof(GameObjectManager));
    gameObjectManager->gameObjectList = ConstructDoublyLinkedList();
    gameObjectManager->nextGameObjectID = 0;
    gameObjectManager->root = ConstructGameObject();
    SetObjectName((Object*)gameObjectManager->root, "Root");
}

void DeinitializeGameObjectManager()
{
    //deconstruct all components in list
    //here//
    free(gameObjectManager);
}

//=========================================================
///////////////////////////////////////////////////////////
/////GAME OBJECT CONSTRUCTION & DECONSTRUCTION/////////////
///////////////////////////////////////////////////////////
//=========================================================

//initialize game object
void InitializeGameObject(GameObject* gameObject)
{
    //initialize base object through object manager
    InitializeObject(&gameObject->base);
    //initialize gameobject
    gameObject->gameObjectID = gameObjectManager->nextGameObjectID;
    //initialize linked list
    gameObject->components = ConstructDoublyLinkedList();
    //children list
    gameObject->children = ConstructDoublyLinkedList();
    if(gameObjectManager->nextGameObjectID != 0)
    {
        GameObjectAddChild(GetRootGameObject(), gameObject);
        //set gameobjects parent to the root
        gameObject->parent = GetRootGameObject();
    }
    else
    {
        //if root, set parent to NULL
        gameObject->parent = NULL;
    }
    //add to object list
    DoublyLinkedListInsertToTail(gameObjectManager->gameObjectList, ConstructDoublyNode((Object*)gameObject));
    gameObjectManager->nextGameObjectID++;
}

//construct game object
GameObject* ConstructGameObject()
{
    GameObject* gameObject = (GameObject*)malloc(sizeof(GameObject));
    InitializeGameObject(gameObject);
    return gameObject;
}

//deconstruct game object
void DeconstructGameObject(GameObject* gameObject)
{
    //deconstruct object through object manager
    DeconstructObject(&gameObject->base);
    //deconstuct all children of linked list
    //here//

    //free game object
    free(gameObject);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////Game Object / Component Functions///////////////
///////////////////////////////////////////////////////////
//=========================================================

//get component of a specific type from a game object
Component* GameObjectGetComponentByType(GameObject* gameObject, ComponentType type)
{
    DoublyNode* currentComponentNode = gameObject->components->head; 
    Component* currentComponent = NULL;

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
    if(component->gameObject != NULL)
    {
        return GameObjectGetComponentByType(component->gameObject, type);
    }
    return NULL;
}


void UpdateAllComponentsInGameObject(GameObject* gameObject)
{
    DoublyNode* currentNode = gameObject->components->head;
    Component* currentComponent = NULL;

    //loop through all components
    while(currentNode != NULL)
    {
        //set current component to next element in list
        currentComponent = (Component*)currentNode->data;
        UpdateComponent(currentComponent);
        //move to next component in list
        currentNode = currentNode->next;
    }
}

void AddComponentToGameObject(GameObject* gameObject, ComponentType type)
{
    Component* component = ConstructComponent(type);
    SetGameObjectOfComponent(component, gameObject);
    DoublyLinkedListInsertToTail(gameObject->components, ConstructDoublyNode((Object*)component));
}

//=========================================================
///////////////////////////////////////////////////////////
///////////GAMOBJECT / GAMEOBJECT FUNCTIONS////////////////
///////////////////////////////////////////////////////////
//=========================================================

//update game object
void GameObjectUpdate(GameObject* gameObject)
{
    //if game object not null & is active
    if(gameObject != NULL && gameObject->base.isActive)
    {
        UpdateAllComponentsInGameObject(gameObject);
    }
}

//update all gameobjects
void UpdateAllGameObjects()
{
    DoublyNode* currentNode = gameObjectManager->gameObjectList->head;
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

void GameObjectAddChild(GameObject* parent, GameObject* child)
{
    DoublyLinkedListInsertToTail(parent->children, ConstructDoublyNode((Object*)child));
}

void GameObjectRemoveChild(GameObject* parent, GameObject* child)
{

}

GameObject* GameObjectGetParent(GameObject* child)
{
    DoublyNode* currentNode = gameObjectManager->gameObjectList->head;
    GameObject* currentGameObject = NULL;

    while(currentNode != NULL)
    {
        currentGameObject = (GameObject*)currentNode->data;
        //loop through children list
        DoublyNode* currentChildNode = currentGameObject->children->head;
        GameObject* currentChild = NULL;
        while(currentChildNode != NULL)
        {
            currentChild = (GameObject*)currentChildNode->data;
            if(currentChild == child)
            {
                return currentGameObject;
            }
            currentChildNode = currentChildNode->next;
        }
        currentNode = currentNode->next;
    }
}

#endif // GAME_OBJECT_MANAGER_C