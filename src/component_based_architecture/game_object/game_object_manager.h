#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H
#include "game_object.h"
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

#endif //GAME_OBJECT_MANAGER_H