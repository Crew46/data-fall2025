#ifndef BASIC_BASE_MANAGER_H
#define BASIC_BASE_MANAGER_H
#include "data_structures/doubly_linked_list/doubly_linked_list.h"

struct BasicManager
{
    DoublyLinkedList* list;
};

void AddObjectToManagerList(Object* object);

#endif //BASIC_BASE_MANAGER_H