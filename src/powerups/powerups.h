#ifndef _POWERUPS_H
#define _POWERUPS_H

// standard libraries
#include "misc.h"
#include "video.h"
#include "input.h"
#include "math.h"
// custom libraries
#include "../object.h"
#include "../data_structures/doubly_linked_list/doubly_linked_list.h"

// declarations

List *powerUpList  = createList();

enum PowerUpType
{
    POWERUP_TYPE_MAXHP,
    POWERUP_TYPE_UPGRADE,
	POWERUP_TYPE_LASER,
	POWERUP_TYPE_MISSILE
};

struct PowerUp
{
    Object       object;
    PowerUpType  type;
    float        duration;
    float        age;
};

PowerUp* CreatePowerUp (int textureID, int *regions, int num_regions, int x, int y, int status, PowerUpType type, float duration)
{
    PowerUp *powerUp                 = (PowerUp *) malloc (sizeof (PowerUp));
    initObject (&powerUp -> object,
                Object_Type_PowerUp,
                textureID,
                regions,
                num_regions,
                x, y,
                status);

    powerUp -> object.index          = 1;
    powerUp -> object.dx             = 0;
    powerUp -> object.dy             = 1;

    powerUp -> type                  = type;
    powerUp -> duration              = duration;
    powerUp -> age                   = 0.0;
    powerUp -> object.angle          = 0.0;
    powerUp -> object.direction      = rand () % 2;
    if (powerUp -> object.direction == 0)
    {
        powerUp -> object.direction  = -1;
    }
    powerUp -> object.direction     *= 4;

    powerUpList                      = append (powerUpList, powerUpList -> tail,
                                               createNode (&powerUp -> object));
}

//return linked list of powerUps
List* GetPowerUpList ()
{
    return powerUpList;
}

void DeconstructPowerUp (PowerUp* powerUp)
{
    free (powerUp);
}

void PowerUpUpdate (PowerUp *powerUp)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // process power-up age / time on screen
    //
    powerUp -> age               += 1.0 / 60.0 * (float)FRAME_SLICES;
    if (powerUp -> age           >  powerUp -> duration)
    {
        powerUp -> object.status |= DELETION_FLAG;
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // move the power-up
    //
    powerUp -> object.y          += powerUp -> object.dy;
}

//update all powerUps
void UpdateAllPowerUps ()
{
    //loop through all instances of powerUps
    Node* currentNode = powerUpList -> head;
    Node* nextNode;

    while (currentNode != NULL)
    {
        nextNode = currentNode -> next;
        if (currentNode -> data != NULL)
        {
            PowerUpUpdate ((PowerUp*)currentNode -> data);
            if (currentNode -> data -> status & DELETION_FLAG)
            {
                DeconstructPowerUp ((PowerUp*)currentNode -> data);
                powerUpList  = obtain (powerUpList, &currentNode);
                deleteNode (currentNode);
            }
        }

        currentNode = nextNode;
    }
}

#endif // _POWERUPS_H
