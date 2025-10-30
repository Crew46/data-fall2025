#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H
#include "../game_object/game_object.h"
#include "../component/component.h"
#include "../../data_structures/doubly_linked_list/doubly_linked_list.h"

//forward declaration of game object manager
struct GameObjectManager
{
    DoublyLinkedList* gameObjectList; //list of game objects
    int nextGameObjectID; //keeps track of the next game object ID to assign
    GameObject* root; //the root of the game object tree
};

//manager initialization
void InitializeGameObjectManager();
void DeinitializeGameObjectManager();

//gameobject creation
void GameObjectManagerInitializeGameObject(GameObject* gameObjectAttatchedTo);
GameObject* GameObjectManagerConstructGameObject();
void GameObjectManagerDeconstructGameObject(GameObject* gameObjectAttatchedTo);

//gameobject-component related functions
Component* GameObjectManagerGameObjectGetComponentByType(GameObject* gameObjectAttatchedTo, ComponentType type);
Component* GameObjectManagerGetComponentFromComponent(Component* component, ComponentType componentType);
void GameObjectManagerUpdateAllComponentsInGameObject(GameObject* gameObjectAttatchedTo);
void GameObjectManagerGameObjectUpdate(GameObject* gameObjectAttatchedTo);
void GameObjectManagerUpdateAllGameObjects();
void GameObjectManagerAddComponentToGameObject(GameObject* gameObjectAttatchedTo, ComponentType type);

//gameobject-gameobject related functions
void GameObjectManagerGameObjectAddChild(GameObject* parent, GameObject* child);
void GameObjectManagerGameObjectRemoveChild(GameObject* parent, GameObject* child);
GameObject* GameObjectManagerGameObjectGetParent(GameObject* child);

//getters and setters
GameObjectManager* GetGameObjectManager();
GameObject* GameObjectManagerGetRootGameObject();


//=========================================================
///////////////////////////////////////////////////////////
///////////GETTERS AND SETTERS/////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

//////////
//OBJECT//
//////////

//set name
void GOM_GameObjectSet_Name(GameObject* gameObject, int* name);
//get name
int* GOM_GameObjectGet_Name(GameObject* gameObject);
//set isactive
void GOM_GameObjectSet_IsActive(GameObject* gameObject, bool isActive);
//get isactive
bool GOM_GameObjectGet_IsActive(GameObject* gameObject);
//get underlying objectid
int GOM_GameObjectGet_ObjectID(GameObject* gameObject);

#endif // GAME_OBJECT_MANAGER_H