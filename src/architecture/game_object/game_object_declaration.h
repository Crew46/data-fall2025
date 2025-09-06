#ifndef GAME_OBJECT_DECLARATION_H
#define GAME_OBJECT_DECLARATION_H
#include "../object/object_declaration.h"
#include "../../data_structures/doubly_linked_list/doubly_linked_list_declaration.h"
#include "../component/component_declaration.h"

struct GameObject
{
    Object base; //base object
    DoublyLinkedList* components; //list of components
    DoublyLinkedList* children; //list of child game objects
    int gameObjectID;
};

#endif // GAME_OBJECT_DECLARATION_H