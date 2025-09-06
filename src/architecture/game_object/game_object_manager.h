#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H
#include "../game_object/game_object.h"
#include "../component/component_manager.h"
#include "../object/object_manager.h"

struct GameObjectManager
{
    DoublyLinkedList* gameObjectList; //list of game objects
    int nextGameObjectID; //keeps track of the next game object ID to assign
    ComponentManager* componentManager; //reference to component manager
    ObjectManager* objectManager; //reference to object manager
};

void InitializeGameObjectManager(GameObjectManager* gameObjectManager, ComponentManager* componentManager, ObjectManager* objectManager);
GameObjectManager* ConstructGameObjectManager(ComponentManager* componentManager, ObjectManager* objectManager);
void DeconstructGameObjectManager(ComponentManager* componentManager);
void GameObjectManagerInitializeGameObject(GameObjectManager* gameObjectManager, GameObject* gameObject, int* name);
GameObject* GameObjectManagerConstructGameObject(GameObjectManager* gameObjectManager, int* name);
void DeconstructGameObject(GameObjectManager* gameObjectManager, GameObject* gameObject);
GameObject* GetGameObjectOfComponent(GameObjectManager* gameObjectManager, Component* component);
Component* GameObjectGetComponentByType(GameObject* gameObject, ComponentType type);
void UpdateAllComponentsInGameObject(GameObject* gameObject);
void GameObjectUpdate(GameObject* gameObject);
void UpdateAllGameObjects(GameObjectManager* gameObjectManager);
void GameObjectManagerAddComponentToGameObject(GameObjectManager* gameObjectManager, GameObject* gameObject, int* componentName, ComponentType type);

#endif // GAME_OBJECT_MANAGER_H