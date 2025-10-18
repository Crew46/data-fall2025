#ifndef QUEUE_H_
#define QUEUE_H_

queue * mkQueue (doublyLinkedList * listB)
{
	queue * myQueue;
	myQueue				= (queue *)malloc(sizeof(queue));	
// Infinite queue
	myQueue->size		= 0;
	myQueue->data		= listB;
	myQueue->front		= listB->head;
	myQueue->back		= listB->tail;
return (myQueue);
}

bool queueIsEmpty (queue * myQueue)
{
	return(myQueue->front == NULL);
}
// add something to the queue
queue * enqueue (queue * myQueue, Object * newNode)
{
	if (myQueue->size != 0)
	{
		if (myQueue->data->qty < myQueue->size)
		{
			if (myQueue->front == NULL)
			{
			myQueue->data	= appendNode (myQueue->data, myQueue->data->tail, newNode);
			myQueue->front	= myQueue->data->head;
			}
			else
			{
			myQueue->data		= appendNode (myQueue->data, myQueue->data->tail, newNode);
			myQueue->back		= myQueue->data->tail;
			}
		}
	}
	else
	{
		if (myQueue->front == NULL)
		{
		myQueue->data = appendNode (myQueue->data, myQueue->data->tail, newNode);
		myQueue->front= myQueue->data->head;
		}
		else
		{
		myQueue->data     = appendNode (myQueue->data, myQueue->data->tail, newNode);
		myQueue->back     = myQueue->data->tail;
		}
	}
return (myQueue);
}
//dequeue will obtain the front and use it.
queue * dequeue (queue * myQueue, Object **thatNode)
{
	if (queueIsEmpty(myQueue) == false)
	{
		myQueue->data 	= obtainNode (myQueue->data, &(myQueue->front));
		(*thatNode)   	= myQueue->front;
		myQueue->front	= myQueue->data->head;
	}
return (myQueue);
}
queue * deleteQueue(queue * myQueue)
{
		if (myQueue->data != NULL)
		{
		myQueue->data	  = clearList(myQueue->data);
		}
		free (myQueue);
		myQueue 		= NULL;
		return (myQueue);
}


#endif // QUEUE_H_
