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
void GOM_Initialize();
void GOM_Deinitialize();

//gameobject creation
void GOM_InitializeGameObject(GameObject* gameObjectAttatchedTo);
GameObject* GOM_ConstructGameObject();
void GOM_DeconstructGameObject(GameObject* gameObjectAttatchedTo);

//gameobject-component related functions
Component* GOM_GameObjectGet_ComponentByType(GameObject* gameObjectAttatchedTo, ComponentType type);
Component* GOM_GetComponentFromComponent(Component* component, ComponentType componentType);
void GOM_UpdateAllComponentsInGameObject(GameObject* gameObjectAttatchedTo);
void GOM_GameObjectUpdate(GameObject* gameObjectAttatchedTo);
void GOM_UpdateAllGameObjects();
void GOM_AddComponentToGameObject(GameObject* gameObjectAttatchedTo, ComponentType type);

//gameobject-gameobject related functions
void GOM_GameObjectAddChild(GameObject* parent, GameObject* child);
void GOM_GameObjectRemoveChild(GameObject* parent, GameObject* child);
GameObject* GOM_GameObjectGetParent(GameObject* child);

//getters and setters
GameObjectManager* GOM_GetGameObjectManager();
GameObject* GOM_GetRootGameObject();


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