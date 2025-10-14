#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

// functions with no identity will go here.
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
Object * mkLaser(Object * player)
{
	Object * laser			= (Object *)malloc(sizeof(Object));
	laser -> isActive      	= true;
	laser -> height        	= 20;
	laser -> width         	= 10;
	laser -> x             	= player -> x + 4;
	laser -> y             	= player->y;
	laser -> next			= NULL;
	laser -> prev			= NULL;
return(laser);
}	




#endif  // _FUNCTIONS_H
