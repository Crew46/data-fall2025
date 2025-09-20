#ifndef OBJECT_H_ 
#define OBJECT_H_

// variables that we will use.
int xpos;
int ypos;
int i;
int status; // status will be used to trigger certain flags
int mask;// mask will change the value of status.
int value; // value is used to check to see if the values match for a flag.
int counter;
int max;
int position;



// The main struct that we use.


struct Object
{
	int x;
	int y;
	int xdir;
	int ydir;
	bool isActive;
	bool laser;
	bool laserFired;
	int speed;
	int height;
	int width;
	Object *head;
	Object *tail;
	Object *next;
	Object *prev;



};

#endif // OBJECT_H_
