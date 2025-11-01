#ifndef GAME_OBJECT_MANAGER_C
#define GAME_OBJECT_MANAGER_C
#include "game_object_manager.h"
#include "../component/component_manager.h"
#include "../object/object_manager.h"
#include "../../data_structures/doubly_linked_list/doubly_linked_list.h"

//declarations
GameObjectManager* gameObjectManager;

GameObjectManager* GOM_GetGameObjectManager()
{
    return gameObjectManager;
}

GameObject* GOM_GetRootGameObject()
{
    return gameObjectManager->root;
}

//=========================================================
///////////////////////////////////////////////////////////
///////////MANAGER INITILIZATION///////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void GOM_Initialize()
{
    gameObjectManager = (GameObjectManager*)malloc(sizeof(GameObjectManager));
    gameObjectManager->gameObjectList = ConstructDoublyLinkedList();
    gameObjectManager->nextGameObjectID = 0;
    gameObjectManager->root = GOM_ConstructGameObject();
    OM_ObjectSet_Name((Object*)gameObjectManager->root, "Root");
}

void GOM_Deinitialize()
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
void GOM_InitializeGameObject(GameObject* gameObject)
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
        GOM_GameObjectAddChild(GOM_GetRootGameObject(), gameObject);
        //set gameobjects parent to the root
        gameObject->parent = GOM_GetRootGameObject();
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
GameObject* GOM_ConstructGameObject()
{
    GameObject* gameObject = (GameObject*)malloc(sizeof(GameObject));
    GOM_InitializeGameObject(gameObject);
    return gameObject;
}

//deconstruct game object
void GOM_DeconstructGameObject(GameObject* gameObject)
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
Component* GOM_GameObjectGet_ComponentByType(GameObject* gameObject, ComponentType type)
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
Component* GOM_GetComponentFromComponent(Component* component, ComponentType type)
{
    if(component->gameObjectAttatchedTo != NULL)
    {
        return GOM_GameObjectGet_ComponentByType(component->gameObjectAttatchedTo, type);
    }
    return NULL;
}

void GOM_GameObjectGet_ComponentsByType(GameObject* gameObjectAttatchedTo, ComponentType type, DoublyLinkedList** out)
{
    *out = ConstructDoublyLinkedList();
    DoublyNode* node = gameObjectAttatchedTo->components->head; 
    while(node != NULL)
    {
        if(((Component*)node->data)->type == type)
        {
            DoublyLinkedListInsertElementToTail(*out, node->data);
        }
        node = node->next;
    }
}


void GOM_UpdateAllComponentsInGameObject(GameObject* gameObject)
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

Component* GOM_AddComponentToGameObject(GameObject* gameObject, ComponentType type)
{
    Component* component = CM_ConstructComponent(type);
    CM_ComponentSet_GameObjectAttatchedTo(component, gameObject);
    DoublyLinkedListInsertElementToTail(gameObject->components, (Object*)component);
    
    //return if attatching was successful
    return component;
}

//=========================================================
///////////////////////////////////////////////////////////
///////////GAMOBJECT / GAMEOBJECT FUNCTIONS////////////////
///////////////////////////////////////////////////////////
//=========================================================

//update game object
void GOM_GameObjectUpdate(GameObject* gameObject)
{
    //if game object not null & is active
    if(gameObject && GOM_GameObjectGet_IsActive(gameObject))
    {
        GOM_UpdateAllComponentsInGameObject(gameObject);
    }
}

//update all gameobjects
void GOM_UpdateAllGameObjects()
{
    DoublyNode* currentNode = gameObjectManager->gameObjectList->head;
    GameObject* currentGameObject = NULL;

    //loop through all game objects
    while(currentNode != NULL)
    {
        //set current game object to next element in list
        currentGameObject = (GameObject*)currentNode->data;

        GOM_GameObjectUpdate(currentGameObject);

        //move to next game object in list
        currentNode = currentNode->next;
    }
}

void GOM_GameObjectAddChild(GameObject* parent, GameObject* child)
{
    DoublyLinkedListInsertElementToTail(parent->children, (Object*)child);
}

void GOM_GameObjectRemoveChild(GameObject* parent, GameObject* child)
{

}

GameObject* GOM_GameObjectGetParent(GameObject* child)
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

//=========================================================
///////////////////////////////////////////////////////////
///////////GETTERS AND SETTERS/////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

//======//
//OBJECT//
//======//

//set name
void GOM_GameObjectSet_Name(GameObject* gameObject, int* name)
{
    OM_ObjectSet_Name((Object*)gameObject, name);
}
//get name
int* GOM_GameObjectGet_Name(GameObject* gameObject)
{
    return OM_ObjectGet_Name((Object*)gameObject);
}
//set isactive
void GOM_GameObjectSet_IsActive(GameObject* gameObject, bool isActive)
{
    OM_ObjectSet_IsActive((Object*)gameObject, isActive);
}
//get isactive
bool GOM_GameObjectGet_IsActive(GameObject* gameObject)
{
    return OM_ObjectGet_IsActive((Object*)gameObject);
}
//get underlying objectid
int GOM_GameObjectGet_ObjectID(GameObject* gameObject)
{
    return OM_ObjectGet_OID((Object*)gameObject);
}

//==========//
//GAMEOBJECT//
//==========//

//=======//
//MANAGER//
//=======//



#endif // GAME_OBJECT_MANAGER_C