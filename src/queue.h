queue * mkQueue(doublyLinkedList * listB)
{
// Infinite queue
	queue->size		= 0;
	queue->data		= listB;
	queue->front	= listB->head;
	queue->back		= listB->tail;
return(myQueue);
}

bool queueIsEmpty(queue * myQueue)
{
	return(queue->front == NULL);
}
// add something to the queue
queue * enqueue(queue * myQueue, Object * newNode, Object * tmp)
{
	if(queue->front == NULL)
	{
	queue->data	= appendNode(queue->data, tmp, newNode);
	queue->front	= queue->data->head;
	}
	else
	{
		queue->data		= appendNode(queue->data, tmp, newNode);
		queue->back		= queue->data->tail;
	}
return(myQueue);
}
queue

