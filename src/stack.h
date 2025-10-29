#ifndef STACK_H // stack.h
#define STACK_H

struct List;
//////////////////////////////////////////////////////////
//
// Stack data structure
//
struct Stack
{
  Node* top;
  DoublyLinkedList* list;
};

Stack* createStack()
{
  Stack* stack = (Stack*)malloc(sizeof(Stack));
  stack->top = NULL;
  stack->list = createList();
}

Stack* push(Stack* stack, Object* newObj)
{
  stack->list = append(stack->list, stack->list->tail, newObj);
  stack->top = stack->list->tail;
  return stack;
}

Node* pop(Stack** stack)
{
  Node* prevTop = obtain(&(*stack)->list, (*stack)->top);
  (*stack)->top = (*stack)->list->tail;

  return prevTop;
}

#endif
