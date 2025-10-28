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
void GameObjectManagerInitializeGameObject(GameObject* gameObject);
GameObject* GameObjectManagerConstructGameObject();
void GameObjectManagerDeconstructGameObject(GameObject* gameObject);

//gameobject-component related functions
Component* GameObjectManagerGameObjectGetComponentByType(GameObject* gameObject, ComponentType type);
Component* GameObjectManagerGetComponentFromComponent(Component* component, ComponentType componentType);
void GameObjectManagerUpdateAllComponentsInGameObject(GameObject* gameObject);
void GameObjectManagerGameObjectUpdate(GameObject* gameObject);
void GameObjectManagerUpdateAllGameObjects();
void GameObjectManagerAddComponentToGameObject(GameObject* gameObject, ComponentType type);

//gameobject-gameobject related functions
void GameObjectManagerGameObjectAddChild(GameObject* parent, GameObject* child);
void GameObjectManagerGameObjectRemoveChild(GameObject* parent, GameObject* child);
GameObject* GameObjectManagerGameObjectGetParent(GameObject* child);

//getters and setters
GameObjectManager* GetGameObjectManager();
GameObject* GameObjectManagerGetRootGameObject();

#endif // GAME_OBJECT_MANAGER_H