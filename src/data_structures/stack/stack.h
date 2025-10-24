#ifndef STACK_H
#define STACK_H
#include "../doubly_linked_list/doubly_linked_list.h"
#include "../doubly_linked_list/doubly_node.h"

struct Stack
{
    DoublyLinkedList* list;
};

//add node to stack
void Stack(DoublyNode* doublyNode);

//remove node from stack and return it
DoublyNode* Unstack(Stack* stack);

//see the next node in the stack
DoublyNode* Peak();

#endif //STACK_H