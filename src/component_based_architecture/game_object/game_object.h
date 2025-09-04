#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "../object/object.h"
#include "../component/component.h"
#include "../../data_structures/doubly_linked_list/doubly_linked_list.h"

struct GameObject
{
    Object base; //base object
    DoublyLinkedList* components; //list of components
    int gameObjectID;
};

GameObject* CreateGameObject(int gameObjectID)
{
    GameObject* gameObject = malloc(sizeof(GameObject));
    //initialize base object through object manager
    //initialize gameobject
    gameObject->gameObjectID = gameObjectID;

    //initialize linked list

    //return object
    return gameObject; 
}

void DeconstructGameObject(GameObject* gameObject)
{
    //deinitialize object through object manager 
    //free game object
    free(gameObject);
}

#endif // GAME_OBJECT_H