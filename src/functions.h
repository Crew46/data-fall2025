#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

// functions with no identity will go here.

//Collision function
bool collision (Object *Thing1, Object *Thing2)
{
    bool  result                                   = true;

    // if Thing1 X > Thing2 X + width/2 + width there is no collision
    if ((Thing1 -> x - Thing1 -> width / 2)       >= (Thing2 -> x + Thing2 -> width / 2))
    {
        result                                     = false;
    }

    // if Thing1 X + width/2 < Thing2 there is no collision
    else if ((Thing1 -> x + Thing1 -> width / 2)  <= (Thing2 -> x - Thing2 -> width / 2))
    {    
        result                                     = false;
    }

    // if Thing1 Y > Thing2Y + height/2 there is no collision
    else if ((Thing1 -> y - Thing1 -> height / 2) >= (Thing2 -> y + Thing2 -> height / 2))
    {    
        result                                     = false;
    }

    // if Thing1 + height/2 < Thing2 y there is no collision
    else if ((Thing1 -> y + Thing1 -> height / 2) <= (Thing2 -> y - Thing2 -> height / 2))
    {    
        result                                     = false;
    }

    return (result);
}
// Bitmasking functions
// int b is the mask. int i is the operation number
int bitMasking ( int b, int i)
{
	mask = b;
// bitwise AND
	if ( i == 0)
	{
		value = status & mask;
	}
// bitwise OR
	if ( i == 1)
	{
		value = status | mask;
	}
// bitwise XOR
	if ( i == 2)
	{
		value = status ^ mask;
	}
// bitwise NOT
	if ( i == 3)
	{
		value = ~status;
	}
return (value);
}

// Used to make ammo for the ammo list
Object * mkAmmo(Object * player)
{
	Object * ammo			= (Object *)malloc(sizeof(Object));
	ammo  -> isActive      	= true;
	ammo -> height        	= 3;
	ammo -> width         	= 9;
	ammo -> x             	= player -> x;
	ammo -> y             	= player -> y;
	ammo -> next			= NULL;
	ammo -> prev			= NULL;
	if (bitMasking (0x00000100, 0) == 0x00000100)
	{
		ammo -> type = 0;
		ammo -> texture = LASER_TEXTURE;
		ammo -> region  = LASER_REGION;
		ammo -> hp 		= 1;
		ammo -> damage	= 1;
	}
return(ammo);
}	

Object * mkPowerup (Object * enemy)
{
	Object * powerup		= (Object *)malloc(sizeof(Object));
	powerup -> isActive		= true;
	powerup -> height		= 11;
	powerup -> width		= 11;
	powerup -> x			= enemy -> x;
	powerup -> y			= enemy -> y;
	powerup -> texture		= SHIELD_TEXTURE;
	powerup -> region		= SHIELD_REGION;
	powerup -> powerup		= true;
	powerup -> next			= NULL;
	powerup -> prev			= NULL;
return(powerup);
}

// Make the player
Object * mkPlayer()
{
	Object *player       = (Object *) malloc (sizeof (Object) * 1);
	player-> next 		 = NULL;
	player-> prev		 = NULL;
	player-> x			 = 360;
	player-> y			 = 300;
	player-> isActive	 = true;
	player-> height		 = 32;
	player-> width		 = 32;
	player -> texture    = PLAYER_TEXTURE;
	player -> region     = PLAYER_REGION;
return(player);
}

#endif  // _FUNCTIONS_H
