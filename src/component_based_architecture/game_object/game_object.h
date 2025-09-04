#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "../component/component_manager.h"
#include "../../data_structures/doubly_linked_list/doubly_linked_list.h"

struct GameObject
{
    Object base; //base object
    DoublyLinkedList* components; //list of components
    DoublyLinkedList* children; //list of child game objects
    int gameObjectID;
};

GameObject* InitializeGameObject(GameObject* gameObject, int* name, int gameObjectID)
{
    //initialize base object through object manager
    ObjectManagerInitializeObject(&gameObject->base, name);
    //initialize gameobject
    gameObject->gameObjectID = gameObjectID;
    //initialize linked list
    gameObject->components = CreateDoublyLinkedList();
}

void DeconstructGameObject(GameObject* gameObject)
{
    //deconstruct object through object manager
    ObjectManagerDeconstructObject(&gameObject->base);
    //deconstuct all children of linked list
    //here//

    //free game object
    free(gameObject);
}

void GameObjectAddComponent(GameObject* gameObject, Component* component)
{
    //add component to linked list of components
    DoublyLinkedListInsertAtTail(gameObject->components, (Object*)component);
}

void GameObjectRemoveComponent(GameObject* gameObject, Component* component)
{
    //remove component from linked list of components
    //DoublyLinkedListRemoveNode(gameObject->components, (Object*)component);
}


#endif // GAME_OBJECT_H