#ifndef QUEUE_H // queue.h
#define QUEUE_H

////////////////////////////////////////////////////////////////
//
// Queue structure
//
struct Queue
{
  Node* front;
  Node* back;
  DoublyLinkedList* list;
};

Queue* createQueue()
{
  Queue* queue = (Queue*)malloc(sizeof(Queue));
  queue->list = createList();
  queue->front = NULL;
  queue->back = NULL;

  return queue;
}

Queue* enqueue(Queue* queue, Object* newObj)
{
  queue->list = insert(queue->list, queue->list->head, newObj);
  queue->front = queue->list->head;
  queue->back = queue->list->tail;

  return queue;
}

Node* dequeue(Queue** queue)
{
  Node* prevFront = obtain(&(*queue)->list, (*queue)->list->head);
  (*queue)->front = (*queue)->list->head;
  (*queue)->back = (*queue)->list->tail;

  return prevFront;

}

#endif
