#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_


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





#endif  //FUNCTIONS_H_
