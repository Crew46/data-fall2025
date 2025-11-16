#ifndef NODE_H
#define NODE_H

// This will make a node for either enemy or enemy (more will be added.)


//Types for things other than ammo. 0 = normal enemy, 1 = boss, 2 = powerup, 3 = enemy laser.
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
	enemy -> type			= 0;

    if (pickVariant        <= 80)
    {
        enemy -> height     = 10;
        enemy -> width      = 10;
        enemy -> hp         = 1;
        enemy -> texture    = ENEMYA_TEXTURE;
        enemy -> region     = ENEMYA_REGION;
        enemy -> points     = rand ()  % ( 20 + 1);
    }
    else
    {
        enemy -> height     = 20;
        enemy -> width      = 20;
        enemy -> hp         = 3;
        enemy -> texture    = ENEMYB_TEXTURE;
        enemy -> region     = ENEMYB_REGION1;
        enemy -> points     = 20;
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
	boss -> hp 		= 50;
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
	


#endif // NODE_H
