#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H
#include "../game_object/game_object.h"
#include "../component/component.h"
#include "../../data_structures/doubly_linked_list/doubly_linked_list.h"

struct GameObjectManager
{
    DoublyLinkedList* gameObjectList; //list of game objects
    int nextGameObjectID; //keeps track of the next game object ID to assign
};

void InitializeGameObjectManager();
void DeinitializeGameObjectManager();
void GameObjectManagerInitializeGameObject(GameObject* gameObject);
GameObject* GameObjectManagerConstructGameObject();
void DeconstructGameObject(GameObject* gameObject);
GameObject* GetGameObjectOfComponent(Component* component);
Component* GameObjectGetComponentByType(GameObject* gameObject, ComponentType type);
void UpdateAllComponentsInGameObject(GameObject* gameObject);
void GameObjectUpdate(GameObject* gameObject);
void UpdateAllGameObjects();
void GameObjectManagerAddComponentToGameObject(GameObject* gameObject, ComponentType type);
GameObjectManager* GetGameObjectManager();
#endif // GAME_OBJECT_MANAGER_H