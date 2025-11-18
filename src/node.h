#ifndef NODE_H
#define NODE_H

// This will make a node for either enemy or enemy (more will be added.)


//Types for things other than ammo. 0 = normal enemy, 1 = boss, 2 = powerup, 3 = laser enemy. 4 = enemy laser.
Object *mkNode ()
{
    Object *enemy           = NULL;
    int     pickVariant     = 0;
    int     xpos            = 0;
    int     ypos            = 0;

    pickVariant             = rand () % (100 + 1);
    xpos                    = rand () % (639 + 1);

    enemy                   = (Object *) malloc (sizeof (Object));

    enemy -> next           = NULL;
    enemy -> prev           = NULL;
    enemy -> x              = xpos;
    enemy -> y              = ypos;
    enemy -> isActive       = true;

    if (pickVariant        <= 70)
    {
        enemy -> height     = 10;
        enemy -> width      = 10;
        enemy -> hp         = 1;
        enemy -> texture    = ENEMYA_TEXTURE;
        enemy -> region     = ENEMYA_REGION;
        enemy -> points     = rand ()  % ( 20 + 1);
		enemy -> type		= 0;
    }
    if ( pickVariant	   >= 71 && pickVariant <= 85)
    {
        enemy -> height     = 20;
        enemy -> width      = 20;
        enemy -> hp         = 3;
        enemy -> texture    = ENEMYB_TEXTURE;
        enemy -> region     = ENEMYB_REGION1;
        enemy -> points     = 20;
		enemy -> type		= 0;
	}
	if ( pickVariant	   >= 86)
	{
		enemy -> height 	= 20;
		enemy -> width		= 20;
		enemy -> hp			= 2;
		enemy -> texture	= ENEMYC_TEXTURE;
		enemy -> region		= ENEMYC_REGION;
		enemy -> points		= 30;
		enemy -> type		= 3;
    }
    return (enemy);
}
// Used to make bosses
Object * mkBoss(Object * player)
{
	Object * boss 	= NULL;
	boss 			= (Object *)malloc(sizeof(Object));
	boss ->	next	= NULL;
	boss -> prev	= NULL;
	boss -> x		= player -> x;
	boss -> y		= -30;
	boss -> isActive= true;
	boss -> type	= 1;
	boss -> height  = 100;
	boss -> width	= 100;
	boss -> hp 		= 40;
	boss -> texture = BOSSA_TEXTURE;
	boss -> region  = BOSSA_REGION;
	boss -> points	= 200;
return(boss);
}
// Used to make boss pawns.
Object * mkPawn (Object * boss)
{
	Object * pawn 	= NULL;
	pawn			= (Object *) malloc(sizeof(Object));
	pawn -> next	= NULL;
	pawn -> prev	= NULL;
	pawn -> x		= boss -> x + rand () % 40 - 40;
	pawn -> y       = boss -> y + 50;
	pawn -> isActive= true;
	pawn -> type	= 0;
	pawn -> height  = 30;
	pawn -> width	= 30;
	pawn -> hp 		= 5;
	pawn -> texture = PAWNA_TEXTURE;
	pawn -> region	= PAWNA_REGION;
	pawn -> points	= 50;
return (pawn);
}
//Used to make enemy lasers (Must be a type 3)
Object * mkEnemyLaser ( Object * enemy) 
{
	Object * EnemyLaser 	= NULL;
	EnemyLaser 				= (Object *) malloc(sizeof(Object));
	EnemyLaser -> next		= NULL;
	EnemyLaser -> prev		= NULL;
	EnemyLaser -> x			= enemy -> x;
	EnemyLaser -> y			= enemy -> y;
	EnemyLaser -> isActive	= true;
	EnemyLaser -> type		= 4;
	EnemyLaser -> height	= 9;
	EnemyLaser -> width		= 3;
	EnemyLaser -> texture	= ENEMYLASER_TEXTURE;
	EnemyLaser -> region	= ENEMYLASER_REGION;
return (EnemyLaser);
}
	


#endif // NODE_H
