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

GameObject* GameObjectManagerGetRootGameObject()
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
    gameObjectManager->root = GameObjectManagerConstructGameObject();
    OM_ObjectSet_Name((Object*)gameObjectManager->root, "Root");
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
void GameObjectManagerInitializeGameObject(GameObject* gameObject)
{
    //initialize base object through object manager
    OM_InitializeObject((Object*)gameObject);
    //initialize gameobject
    gameObject->GID = gameObjectManager->nextGameObjectID;
    //initialize linked list
    gameObject->components = ConstructDoublyLinkedList();
    //children list
    gameObject->children = ConstructDoublyLinkedList();
    //if not root game object
    if(gameObjectManager->nextGameObjectID != 0)
    {
        GameObjectManagerGameObjectAddChild(GameObjectManagerGetRootGameObject(), gameObject);
        //set gameobjects parent to the root
        gameObject->parent = GameObjectManagerGetRootGameObject();
    }
    else
    {
        //if root, set parent to NULL
        gameObject->parent = NULL;
    }
    //add to object list
    DoublyLinkedListInsertElementToTail(gameObjectManager->gameObjectList, (Object*)gameObject);
    gameObjectManager->nextGameObjectID++;
}

//construct game object
GameObject* GameObjectManagerConstructGameObject()
{
    GameObject* gameObject = (GameObject*)malloc(sizeof(GameObject));
    GameObjectManagerInitializeGameObject(gameObject);
    return gameObject;
}

//deconstruct game object
void GameObjectManagerDeconstructGameObject(GameObject* gameObject)
{
    //deconstruct object through object manager
    OM_DeconstructObject(&gameObject->base);
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
Component* GameObjectManagerGameObjectGetComponentByType(GameObject* gameObject, ComponentType type)
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
Component* GameObjectManagerGetComponentFromComponent(Component* component, ComponentType type)
{
    if(component->gameObjectAttatchedTo != NULL)
    {
        return GameObjectManagerGameObjectGetComponentByType(component->gameObjectAttatchedTo, type);
    }
    return NULL;
}


void GameObjectManagerUpdateAllComponentsInGameObject(GameObject* gameObject)
{
    DoublyNode* currentNode = gameObject->components->head;
    Component* currentComponent = NULL;

    //loop through all components
    while(currentNode != NULL)
    {
        //set current component to next element in list
        currentComponent = (Component*)currentNode->data;

        CM_UpdateComponent(currentComponent);

        //move to next component in list
        currentNode = currentNode->next;
    }
}

void GameObjectManagerAddComponentToGameObject(GameObject* gameObject, ComponentType type)
{
    Component* component = CM_ConstructComponent(type);
    CM_ComponentSet_GameObjectAttatchedTo(component, gameObject);
    DoublyLinkedListInsertElementToTail(gameObject->components, (Object*)component);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////GAMOBJECT / GAMEOBJECT FUNCTIONS////////////////
///////////////////////////////////////////////////////////
//=========================================================

//update game object
void GameObjectManagerGameObjectUpdate(GameObject* gameObject)
{
    //if game object not null & is active
    if(gameObject != NULL && ((Object*)gameObject)->isActive)
    {
        GameObjectManagerUpdateAllComponentsInGameObject(gameObject);
    }
}

//update all gameobjects
void GameObjectManagerUpdateAllGameObjects()
{
    DoublyNode* currentNode = gameObjectManager->gameObjectList->head;
    GameObject* currentGameObject = NULL;

    //loop through all game objects
    while(currentNode != NULL)
    {
        //set current game object to next element in list
        currentGameObject = (GameObject*)currentNode->data;

        GameObjectManagerGameObjectUpdate(currentGameObject);

        //move to next game object in list
        currentNode = currentNode->next;
    }
}

void GameObjectManagerGameObjectAddChild(GameObject* parent, GameObject* child)
{
    DoublyLinkedListInsertElementToTail(parent->children, (Object*)child);
}

void GameObjectManagerGameObjectRemoveChild(GameObject* parent, GameObject* child)
{

}

GameObject* GameObjectManagerGameObjectGetParent(GameObject* child)
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