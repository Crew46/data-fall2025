#ifndef GAME_OBJECT_MANAGER_C
#define GAME_OBJECT_MANAGER_C
#include "game_object_manager.h"

//=========================================================
///////////////////////////////////////////////////////////
///GAME OBJECT MANAGER CONSTRUCTION & DECONSTRUCTION///////
///////////////////////////////////////////////////////////
//=========================================================

void InitializeGameObjectManager(GameObjectManager* gameObjectManager, ComponentManager* componentManager, ObjectManager* objectManager)
{
    gameObjectManager->gameObjectList = CreateDoublyLinkedList();
    gameObjectManager->nextGameObjectID = 0;
    gameObjectManager->componentManager = componentManager;
    gameObjectManager->objectManager = objectManager;
}

GameObjectManager* ConstructGameObjectManager(ComponentManager* componentManager, ObjectManager* objectManager)
{
    GameObjectManager* gameObjectManager = (GameObjectManager*)malloc(sizeof(GameObjectManager));
    InitializeGameObjectManager(gameObjectManager, componentManager, componentManager->objectManager);
    return gameObjectManager;
}

void DeconstructGameObjectManager(ComponentManager* componentManager)
{
    //deconstruct all components in list
    //here//
    //free component manager struct
    free(componentManager);
}

//=========================================================
///////////////////////////////////////////////////////////
/////GAME OBJECT CONSTRUCTION & DECONSTRUCTION/////////////
///////////////////////////////////////////////////////////
//=========================================================

//initialize game object
void GameObjectManagerInitializeGameObject(GameObjectManager* gameObjectManager, GameObject* gameObject)
{
    //initialize base object through object manager
    ObjectManagerInitializeObject(gameObjectManager->objectManager, &gameObject->base);
    //initialize gameobject
    gameObject->gameObjectID = gameObjectManager->nextGameObjectID;
    gameObjectManager->nextGameObjectID++;
    //initialize linked list
    gameObject->components = CreateDoublyLinkedList();
    //add to object list
    DoublyLinkedListInsertAtTail(gameObjectManager->gameObjectList, (Object*)gameObject);
}

//construct game object
GameObject* GameObjectManagerConstructGameObject(GameObjectManager* gameObjectManager)
{
    GameObject* gameObject = (GameObject*)malloc(sizeof(GameObject));
    GameObjectManagerInitializeGameObject(gameObjectManager, gameObject);
    return gameObject;
}

//deconstruct game object
void DeconstructGameObject(GameObjectManager* gameObjectManager, GameObject* gameObject)
{
    //deconstruct object through object manager
    ObjectManagerDeconstructObject(gameObjectManager->objectManager, &gameObject->base);
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

//find the game object that a component belongs to
GameObject* GetGameObjectOfComponent(GameObjectManager* gameObjectManager, Component* component)
{
    DoublyNode* currentGameObjectNode = gameObjectManager->gameObjectList->head;
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
Component* GetComponentFromComponent(GameObjectManager* gameObjectManager, Component* component, ComponentType type)
{
    GameObject* gameObject = GetGameObjectOfComponent(gameObjectManager, component);
    if(gameObject != NULL)
    {
        return GameObjectGetComponentByType(gameObject, type);
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
void UpdateAllGameObjects(GameObjectManager* gameObjectManager)
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

void GameObjectManagerAddComponentToGameObject(GameObjectManager* gameObjectManager, GameObject* gameObject, ComponentType type)
{
    Component* component = ComponentManagerConstructComponent(gameObjectManager->componentManager, type);
    DoublyLinkedListInsertAtTail(gameObject->components, (Object*)component);
}

#endif // GAME_OBJECT_MANAGER_C