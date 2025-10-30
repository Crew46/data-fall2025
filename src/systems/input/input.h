#ifndef INPUT
#define INPUT
#include "../../vector/vector2.h"

struct Input
{
    int buttonA;
    int buttonB;
    int buttonX;
    int buttonY;
    int buttonL;
    int buttonR;
    int buttonStart;
    Vector2 movementDirection;
    Vector2 normalizedMovementDirection;
};

#endif //INPUT