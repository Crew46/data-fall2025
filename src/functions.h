#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
// prepping what we need;
doublyLinkedList * listA;
stack	* myStack;
Object 	* tmp;
Object 	* tmp2;
Object 	* tmp3;
Object 	* newNode;
Object 	* laser;

bool collision( Object* Thing1, Object * Thing2)
{
// if Thing1 X > Thing2 X + width/2 + width there is no collision
if (( Thing1->x - Thing1->width/2) >= (Thing2->x + Thing2->width/2) )
	return false;
// if Thing1 X + width/2 < Thing2 there is no collision
if (( Thing1->x + Thing1->width/2) <= (Thing2->x - Thing2->width/2) )
	return false;
// if Thing1 Y > Thing2Y + height/2 there is no collision
if (( Thing1->y - Thing1->height/2) >= (Thing2->y + Thing2->height/2) )
	return false;
// if Thing1 + height/2 < Thing2 y there is no collision
if (( Thing1->y + Thing1->height/2) <= (Thing2->y - Thing2->height/2) )
	return false;
// If it makes it here then there is a collision
	return true;
}

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


// This will make a node for either EnemyA or EnemyB (more will be added.)
Object * mkNode()
{
	a       =   rand() % ( 100 + 1);
	xpos    =   rand() % ( 639 + 1);
	if(a <= 80)
	{
	Object * EnemyA         = (Object *) malloc (sizeof (Object));
	EnemyA ->next           = NULL;
	EnemyA ->prev           = NULL;
	EnemyA -> x             = xpos;
	EnemyA -> y             = ypos;
	EnemyA -> height        = 10;
	EnemyA -> width         = 10;
	EnemyA -> isActive      = true;
	EnemyA -> hp            = 1;
	EnemyA -> texture       = ENEMYA_TEXTURE;
	EnemyA -> region        = ENEMYA_REGION;
	return(EnemyA);
	}
	if(a > 80)
	{
	Object * EnemyB         = (Object *) malloc (sizeof(Object));
	EnemyB -> next          = NULL;
	EnemyB -> prev          = NULL;
	EnemyB -> x             = xpos;
	EnemyB -> y             = ypos;
	EnemyB -> height        = 20;
	EnemyB -> width         = 20;
	EnemyB -> isActive      = true;
	EnemyB -> hp            = 3;
	EnemyB -> texture       = ENEMYB_TEXTURE;
	EnemyB -> region        = ENEMYB_REGION;
	return(EnemyB);
	}
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





#endif  //FUNCTIONS_H_
