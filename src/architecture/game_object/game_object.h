#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "../object/object.h"
#include "../../data_structures/doubly_linked_list/doubly_linked_list.h"

//forward declaration of game object
struct GameObject
{
    Object base; //base object
    DoublyLinkedList* components; //list of components
    DoublyLinkedList* children; //list of child game objects
    int gameObjectID;
};

#endif // GAME_OBJECT_H