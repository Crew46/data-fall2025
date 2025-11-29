#ifndef NODE_H
#define NODE_H

// This will make a node for either enemy or enemy (more will be added.)


//Types for things other than ammo. 0 = normal enemy, 1 = boss, 2 = powerup, 3 = laser enemy. 4 = enemy laser.
// 5 = EnemyD which bounces around.
Object *mkNode (int x, int y, int pickVariant, int movement)
{
    Object *enemy           = NULL;
    int     xpos            = x;
    int     ypos            = y;

    enemy                   = (Object *) malloc (sizeof (Object));

    enemy -> next           = NULL;
    enemy -> prev           = NULL;
    enemy -> x              = xpos;
    enemy -> y              = ypos;
    enemy -> isActive       = true;

    if (pickVariant        <= 70)
    {
        enemy -> height     = 9;
        enemy -> width      = 14;
        enemy -> hp         = 1;
        enemy -> texture    = ENEMYA_TEXTURE;
        enemy -> region     = ENEMYA_REGION;
        enemy -> points     = rand ()  % ( 20 + 1);
		enemy -> type		= 0;
		enemy -> movement 	= movement;
    }
    if ( pickVariant	   >= 71 && pickVariant <= 85)
    {
        enemy -> height     = 19;
        enemy -> width      = 19;
        enemy -> hp         = 6;
        enemy -> texture    = ENEMYB_TEXTURE;
        enemy -> region     = ENEMYB_REGION1;
        enemy -> points     = 20;
		enemy -> type		= 0;
		enemy -> movement	= movement;
	}
	if ( pickVariant	   >= 86 && pickVariant <= 91)
	{
		enemy -> height 	= 19;
		enemy -> width		= 19;
		enemy -> hp			= 2;
		enemy -> texture	= ENEMYC_TEXTURE;
		enemy -> region		= ENEMYC_REGION;
		enemy -> points		= 30;
		enemy -> type		= 3;
		enemy -> y			= 50;
		enemy -> xdir		= 2;
// Spawning enemies outside and then they will come in and shoot.
	b = rand() % 2;
			if ( b == 0)
			{
				enemy -> x 			= 690;
				enemy -> movement 	= 0;
			}
			if ( b == 1) 
			{
				enemy -> x			= -30;
				enemy -> movement	= 1;
			}
	}
	if (pickVariant >= 92)
	{
		enemy -> height 	= 29;
		enemy -> width		= 29;
		enemy -> hp			= 6;
		enemy -> texture	= ENEMYD_TEXTURE;
		enemy -> region		= ENEMYD_REGION;
		enemy -> points		= 25;
		enemy -> type		= 5;
		b = rand () % 3;
			if ( b == 0)
			{
				enemy -> movement = 0;
			}
			if ( b == 1)
			{
				enemy -> movement = 1;
			}
			if ( b == 2)
			{
				enemy -> movement = 2;
			}
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
// Used to make ammo for the ammo list.
// Type guide. 0 = Laser and 1 = Rocket.	
Object * mkAmmo (Object * player)
{
	Object * ammo           = (Object *)malloc(sizeof(Object));
	ammo -> isActive		= true;
	ammo -> x               = player -> x;
	ammo -> y               = player -> y;
	ammo -> next            = NULL;
	ammo -> prev            = NULL;
	if (bitMasking (0x00000100, 0) == 0x00000100)
	{
		ammo -> type    = 0;
		ammo -> height  = 9;
		ammo -> width   = 3;
		ammo -> texture = LASER_TEXTURE;
		ammo -> region  = LASER_REGION;
		ammo -> hp 		= 1;
		ammo -> damage	= 6;
	}
	if (bitMasking (0x00000200, 0) == 0x000000200)
	{
		ammo -> type	= 1;
		ammo -> width	= 11;
		ammo -> height	= 11;
		ammo -> texture = ROCKET_TEXTURE;
		ammo -> region  = ROCKET_REGION;
		ammo -> hp		= 1;
		ammo -> damage  = 1;
		}
return (ammo);
}
// Powerups
Object * mkPowerup ( Object * enemy)
{
	Object * powerup	= (Object *)malloc(sizeof(Object));
	powerup -> isActive	= true;
	powerup -> height	= 11;
	powerup -> width	= 11;
	powerup -> x            = enemy -> x;
	powerup -> y            = enemy -> y;
	powerup -> texture      = SHIELD_TEXTURE;
	powerup -> region       = SHIELD_REGION;
	powerup -> type			= 2;
	powerup -> next			= NULL;
	powerup -> prev			= NULL;
return (powerup);
}
// Player
Object * mkPlayer ()
{
	Object *player      = (Object *) malloc (sizeof (Object) * 1);
	player -> next		= NULL;
	player -> prev		= NULL;
	player -> x			= 360;
	player -> y			= 300;
	player -> isActive	= true;
	player -> height	= 32;
	player -> width		= 32;
	player -> texture	= PLAYER_TEXTURE;
	player -> region 	= PLAYER_REGION;
return (player);
}
Object * spawn( Object * newNode)
{
	int pickVariant	= rand () % (100 + 1);
	int c			= rand () % (639 + 1);
	newNode 		= mkNode(c, 0 , pickVariant, 0);
return (newNode);
}
	
#endif // NODE_H
