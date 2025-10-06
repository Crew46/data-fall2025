#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
// prepping what we need;
doublyLinkedList * listA;
stack	* myStack;
Object 	* tmp;
Object 	* tmp2;
Object 	* tmp3;
Object 	* newNode;
Object 	* laser;

// This will make the list
doublyLinkedList * mkList()
{
	doublyLinkedList * listA = (doublyLinkedList *) malloc (sizeof(doublyLinkedList));
	if(listA == NULL)
		{
			exit();
		}
listA->head = NULL;
listA->tail	= NULL;
return(listA);
}

// This function will create a single EnemyA everytime it is used.
doublyLinkedList * appendNode (doublyLinkedList * listA, Object * tmp, Object * newNode )
{
	// If head is NULL then we will put the newNode as the head.
	if(listA->head      	== NULL)
	{
		listA->head         = newNode;
	}
	// Otherwise we move forward
	else
	{
		tmp					= listA->head;
		while(tmp -> next	!= NULL)
		{
			tmp					= tmp->next;
		}
		if(  tmp ->next		== NULL)
		{
			tmp->next			= newNode;
			listA->tail			= tmp->next;
			tmp->next->prev		= tmp;
		}
	}
listA->qty	= listA->qty + 1;
return(listA);
}


//rmNode frees up nodes that we want gone.
doublyLinkedList * rmNode(Object **thatNode, doublyLinkedList * listA)
{
	if((*thatNode) ->isActive    == false)
	{
		free(*thatNode);
		if((*thatNode)			!= NULL)
		{
		(*thatNode)				= NULL;
		}
	}
return(listA);
}


// The obtain function disconnects nodes.
doublyLinkedList * obtainNode(doublyLinkedList * listA, Object **thatNode)
{
	// Obtaining the head edge case.
	if((*thatNode) == listA->head)
	{
		listA->head         = (*thatNode)->next;
		(*thatNode)->next->prev     = NULL;
		(*thatNode)->next           = NULL;
	}
	// Obtain the tail edge case.
	if((*thatNode) == listA->tail)
	{
		listA->tail             = (*thatNode)->prev;
		listA->tail->next       = NULL;
		(*thatNode)->prev       = NULL;
	}	
	// No edge cases. Proceed.
	if((*thatNode) != listA->head && (*thatNode) != listA->tail)
	{
		(*thatNode)->prev->next     = (*thatNode)->next;
		(*thatNode)->next->prev     = (*thatNode)->prev;
		(*thatNode)->next           = NULL;
		(*thatNode)->prev           = NULL;
	}
listA->qty	= listA->qty + 1;
return(listA);
}


//Empty the list.
doublyLinkedList * clearList(doublyLinkedList * listA)
{
	Object * tmp                    = NULL;
	if(listA    != NULL)
	{
		while(tmp   != NULL)
		{
			listA   = obtainNode(listA, &tmp);
			listA   = rmNode(&tmp, listA);
			tmp     = listA->head;
		}
	}
return(listA);
}


// Insert will insert a node before a node.
doublyLinkedList * insertNode ( doublyLinkedList * listA ,Object * tmp, Object * newNode, int position)
{
	// Edge case where we want to replace the head of the list.
	tmp                     = listA->head;
	if(position             == 0)
	{
	listA->head         = newNode;
	listA->head->next   = tmp;
	listA->head->next->prev = listA->head;
	}
// If there is no edge case. Proceed.
	else
	{
		i = 0;
		tmp                     = listA->head;
		while(i != position)
		{
			i = i+1;
			tmp = tmp->next;
		}
	Object *tmp2        = tmp->next;
	tmp ->next          = newNode;
	tmp ->next->prev    = tmp;
	tmp                 = tmp -> next;
	tmp->next           = tmp2;
	tmp2->prev          = tmp;
	}
listA->qty	= listA->qty + 1;
return(listA);
}


// This will delete a list when we no longer need it.
doublyLinkedList * deleteList(doublyLinkedList * listA)
{
	if(listA != NULL)
	{
		listA   = clearList(listA);
		free(listA);
		listA	= NULL;
	}
return(listA);
}





#endif  //LINKEDLIST_H_
