#ifndef COLLISION_H_
#define COLLISION_H_


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

#endif  //COLLISION_H_
