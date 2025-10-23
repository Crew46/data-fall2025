#ifndef _QUEUE_H
#define _QUEUE_H

#include "../doubly_linked_list/doubly_linked_list.h"

struct Queue
{
	List* data;
	int   size;
	int   count;
};

bool enqueue(Queue* queue, Node* newNode)
{
	if(newNode != NULL)
	{
		if(queue->count < queue->size || queue->size < 1)
		{
			insert(queue->data, queue->data->head, newNode);
			queue->count++;
			return true;
		}
	}

	return false;
}

Node* dequeue(Queue* queue)
{
	if(queue->data->tail != NULL)
	{
		Node *node     = queue -> data -> tail;
		queue -> data  = obtain (queue -> data, &node);
		queue->count--;
		return node;
	}
	else
	{
		return NULL;
	}
}

Queue* createQueue(int size)
{
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	queue->data  = createList();
	queue->size  = size;
	queue->count = 0;

	return queue;
}


#endif
