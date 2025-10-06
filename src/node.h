#ifndef NODE_H_
#define NODE_H_

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


















#endif //NODE_H_
