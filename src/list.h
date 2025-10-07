#ifndef LIST_H // list.h
#define LIST_H

////////////////////////////////////////////////////////////////////////////////////
//
//  Doubly Linked List struct and helpers
//
struct DoublyLinkedList
{
  Node* head;
  Node* tail;
};



DoublyLinkedList* deleteNode(DoublyLinkedList* list, Node** node)
{
  if(!list || !node || !*node)
    return list;

  // Only one node
  if(list->head == (*node) && list->tail == (*node))
  {
    list->head = NULL;
    list->tail = NULL;
  }
  else if(*node == list->head)
  {
    list->head = (*node)->next;
    list->head->prev = NULL;
  }
  else if(*node == list->tail)
  {
    list->tail = (*node)->prev;
    list->tail->next = NULL;
  }
  else
  {
    (*node)->next->prev = (*node)->prev;
    (*node)->prev->next = (*node)->next;
  }

  free(*node);
  *node = NULL;

  return list;
}

DoublyLinkedList* createList()
{
  DoublyLinkedList* list = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
  list->head = NULL;
  list->tail = NULL;

  return list;
}

void deleteList(DoublyLinkedList** list)
{
  Node* current = (*list)->head;
  while(current != NULL)
  {
    Node* next = current->next;
    deleteNode((*list), &current);
    current = next;
  }
  free(*list);
  *list = NULL;
}

// Insert a new object
DoublyLinkedList* insert(DoublyLinkedList* list, Node* targetNode, Object* newObj)
{
  if(!list || !newObj)
    return list;

  Node* newNode = createNode(newObj);

  // List is empty
  if( !list->head && !list->tail )
  {
    list->head = newNode;
    list->tail = newNode;
  }
  else if(list->head == targetNode)
  {
    list->head = newNode;
    newNode->next = targetNode;
    targetNode->prev = newNode;
  }
  else
  {
    newNode->prev = targetNode->prev;
    targetNode->prev->next = newNode;
    targetNode->prev = newNode;
    newNode->next = targetNode;
  }

  return list;
}

// Append a new object
DoublyLinkedList* append(DoublyLinkedList* list, Node* targetNode, Object* newObj)
{
  if(!list || !newObj)
    return list;

  Node* newNode = createNode(newObj);

  // List is empty
  if( !list->head && !list->tail )
  {
    list->head = newNode;
    list->tail = newNode;
  }
  else if(list->tail == targetNode)
  {
    list->tail = newNode;
    newNode->prev = targetNode;
    targetNode->next = newNode;
  }
  else
  {
    newNode->next = targetNode->next;
    targetNode->next->prev = newNode;
    targetNode->next = newNode;
    newNode->prev = targetNode;
  }

  return list;
}

Node* obtain(DoublyLinkedList** list, Node* node)
{
  if(!list || !(*list) || !node)
    return NULL;

  // Only one node in the list
  if(node == (*list)->head && node == (*list)->tail)
  {
    (*list)->head = NULL;
    (*list)->tail = NULL;
  }
  else if(node == (*list)->head)
  {
    (*list)->head = node->next;
    node->next->prev = NULL;
    node->next = NULL;
  }
  else if(node == (*list)->tail)
  {
    (*list)->tail = node->prev;
    node->prev->next = NULL;
    node->prev = NULL;
  }
  else
  {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->next = NULL;
    node->prev = NULL;
  }

  return node;
}

#endif
