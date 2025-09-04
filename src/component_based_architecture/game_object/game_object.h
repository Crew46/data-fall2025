#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "../object/object.h"
#include "../component/component.h"
#include "../../data_structures/doubly_linked_list/doubly_linked_list.h"

struct GameObject
{
    Object* base; //base object
    DoublyLinkedList* components; //list of components
};

#endif // GAME_OBJECT_H