#ifndef _PLAYER_H
#define _PLAYER_H
// standard libraries
#include "misc.h"
#include "video.h"
#include "input.h"
#include "math.h"
// custom libraries
#include "../object.h"
#include "../data_structures/doubly_linked_list/doubly_linked_list.h"
#include "../data_structures/queue/queue.h"
#include "../weapon/weapon.h"
#include "../tools/debugger.h"

/*
 * 
 * SUMMARY:
 * this entire file is split into different sections for different concerns regarding
 * the player, including:
 *
 * part 1: the model
 * part 2: visual functions
 * part 3: logical connections between model and view
 * part 4: instance management
 * part 5: construction and desconstruction
 *
 */

// declarations

List *playerList  = createList();

struct Player 
{
    // object is not a pointer, in order to embed to struct for upcasting & downcasting.
    Object  object;
    int     gamepadID;
    Queue  *weapons; // weapon that player has equipped
    int     weaponIndexer;
};

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 1: PLAYER MODEL////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

/*
 * SUMMARY:
 * This is the model of the player: ie. the fundamental 
 * behaviors of the player. logical connection between these functions is in part 3
 */

// move player in a direction, where then direction is scaled by the player's speed
void movePlayer (Player *player)
{
    moveObject (&player -> object);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 2: VISUAL FUNCTIONS////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

/*
 * SUMMARY:
 * this part is for visualizing the data of the model
 */

void DrawPlayer (Player *player)
{
    drawObject (&player -> object);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 3: LOGICAL CONNECTION//////////////////////
///////////////////////////////////////////////////////////
//=========================================================

/*
 * SUMMARY:
 * This part is the glue to making the player model, player 
 * view, and input work together. ie the logic that connects 
 * the player's model, view, and input.
 */

void playerDropWeapon (Player *player)
{
    Node *dropped              = dequeue (player -> weapons);
    if (dropped               != NULL)
    {
        ((Weapon *) dropped -> data) -> hasOwner = false;
        free (dropped);
        dropped                = NULL;

        // accessing dropped after free() is just asking for trouble
    }
}

void playerGrabWeapon (Player *player)
{
    Node   *currentNode                      = GetWeaponList() -> head;
    Weapon *weapon                           = NULL;
    Node   *nextNode                         = NULL;
    int     newStatus                        = 0;
    int     tmpStatus                        = 0;

    while (currentNode                      != NULL)
    {
        nextNode                             = currentNode -> next;
        weapon                               = (Weapon *) currentNode -> data;

        if(weapon -> hasOwner               == false)
        {
            if (collisionCheck (&player -> object, currentNode -> data))
            {
                if (enqueue (player -> weapons, createNode (currentNode -> data)))
                {
                    newStatus                = weapon -> object.status;
                    newStatus                = newStatus & (~TeamFlagMask);
                    tmpStatus                = player -> object.status & TeamFlagMask;
                    newStatus                = newStatus | tmpStatus;

                    weapon -> object.status  = newStatus;
                    weapon -> hasOwner       = true;

                    weapon -> yOffset        = -5;
                    weapon -> xOffset        = -10 + (10 * player -> weaponIndexer);

                    player -> weaponIndexer  = player -> weaponIndexer + 1;
                    player -> weaponIndexer  = player -> weaponIndexer % 3;
                }
            }
        }

        currentNode                          = nextNode;
    }
}

void setWeaponPositions (Player *player)
{
    int     team                   = 0;
    Node   *currentNode            = player -> weapons -> list -> head;
    Node   *nextNode               = NULL;
    Weapon *currentWeapon          = NULL;

    team                           = (player -> object.status & TeamFlagMask);
    team                           = team >> TeamFlagOffset;

    while (currentNode            != NULL)
    {
        nextNode                   = currentNode -> next;
        currentWeapon              = (Weapon *) currentNode -> data;

        int  realX                 = currentWeapon -> xOffset;
        int  realY                 = currentWeapon -> yOffset;

        if ((team % 2)            == 1)
        {
            int  tmp               = realX;
            realX                  = -realY;
            realY                  = tmp;
        }

        if (team                  >= 2)
        {
            realX                  = -realX;
            realY                  = -realY;
        }

        currentWeapon -> object.x  = player -> object.x + realX;
        currentWeapon -> object.y  = player -> object.y + realY;

        currentNode                = nextNode;
    }
}

void playerFireWeapons (Player *player)
{
    bool    fireStatus             = (gamepad_button_a () >  0);

    Node   *currentNode            = player -> weapons -> list -> head;
    Node   *nextNode               = NULL;
    Weapon *currentWeapon          = NULL;

    while (currentNode            != NULL)
    {
        nextNode                   = currentNode -> next;
        currentWeapon              = (Weapon *) currentNode -> data;

        currentWeapon -> isFiring  = fireStatus;

        currentNode                = nextNode;
    }
}

void HandleInput (Player *player)
{
    float  deltaX                       = 0.0;
    float  deltaY                       = 0.0;
    float  roundTmp                     = 0.0;

    // select the gamepad mapped to this player controller
    select_gamepad (player -> gamepadID);
    gamepad_direction_normalized (&deltaX, &deltaY); // get direction from the gamepad
    roundTmp                            = (deltaX * (float) player -> object.vx);
    player -> object.dx                 = round (roundTmp);
    roundTmp                            = (deltaY * (float) player -> object.vy);
    player -> object.dy                 = round (roundTmp);

    movePlayer (player);

    if (player -> weapons -> count     != 0)
    {
        if ((gamepad_button_b () % 30) == 29)
        {
            playerDropWeapon (player);
        }

        setWeaponPositions (player);
        playerFireWeapons (player);
    }

    if ((gamepad_button_b ()           >  1) &&
        (gamepad_button_b ()           <  5))
    {
        playerGrabWeapon (player);
    }
}

void PlayerUpdate (Player *player)
{
    List *lasers        = GetLaserList ();
    Node *currentNode   = lasers -> head;
    Node *nextNode      = NULL;

    if (player -> object.status & IsActiveFlag)
    {
        //handle input every frame
        HandleInput (player);

        // Update the player view every frame
        DrawPlayer (player);
    }

    while (currentNode != NULL)
    {
        nextNode        = currentNode -> next;

        if (((currentNode -> data -> status ^ player -> object.status) & TeamFlagMask) != 0)
        {
            if (collisionCheck (&player -> object, currentNode -> data))
            {
                player -> object.status |= DeletionMarkFlag;
            }
        }

        currentNode     = nextNode;
    }
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 4: CONSTRUCTION////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

//constructor
Player *CreatePlayer (int textureID, int regionID, int x, int y, int status, float maxShootCooldownTime, int gamepadID)
{
    // allocate memory for player
    Player *player           = (Player *) malloc (sizeof (Player));
    Weapon *weapon           = NULL;

    // player object properties initialization
    initObject (&player -> object, Object_Type_Entity, textureID, regionID, x, y, status);

    // player properties initialization
    player -> gamepadID      = gamepadID;

    player -> weapons        = createQueue (3);
    weapon                   = CreateWeapon (WEAPON_TEXTURES, WEAPON_REGION, player->object.x, player->object.y, status, WEAPON_TYPE_LASER_CANNON, maxShootCooldownTime, 2.0);
    enqueue (player -> weapons, createNode (&weapon -> object));
    weapon -> hasOwner       = true;

    player -> weaponIndexer  = 1;

    append (playerList, playerList -> tail, createNode (&player -> object));

    // return pointer to player
    return player;
}

// deconstructor
void DeconstructPlayer (Player *player)
{
    Node *currentNode            = dequeue (player -> weapons);

    while (currentNode          != NULL)
    {
        if (currentNode -> data != NULL)
        {
            ((Weapon *) currentNode -> data) -> hasOwner  = false;
        }
        currentNode              = dequeue (player -> weapons);
    }

    free (player);
    player                       = NULL;
}

void DeconstructPlayerAndWeapon (Player *player)
{
    Node *currentNode                  = player -> weapons -> list -> head;
    Node *nextNode                     = NULL;

    while (currentNode                != NULL)
    {
        nextNode                       = currentNode -> next;

        currentNode -> data -> status |= DeletionMarkFlag;

        currentNode                    = nextNode;
    }

    DeconstructPlayer (player);
}

void DeconstructAllPlayers ()
{
    // loop through all instances of players
    Node *currentNode   = playerList -> head;
    Node *next          = NULL;

    while (currentNode != NULL)
    {
        next            = currentNode -> next;
        DeconstructPlayer ((Player *) currentNode -> data);
        playerList      = obtain (playerList, currentNode);
        deleteNode (currentNode);

        currentNode     = next;
    }
}

void DeconstructAllPlayersAndWeapons ()
{
    // loop through all instances of players
    Node *currentNode   = playerList -> head;
    Node *next          = NULL;

    while (currentNode != NULL)
    {
        next            = currentNode -> next;
        DeconstructPlayerAndWeapon ((Player *) currentNode -> data);
        playerList      = obtain (playerList, currentNode);
        deleteNode (currentNode);

        currentNode     = next;
    }
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 5: INSTANCES MANAGEMENT////////////////////
///////////////////////////////////////////////////////////
//=========================================================

/*
 * SUMMARY: NOT FULLY IMPLEMENTED UNTIL THE COMPLETION OF LINKED LIST
 * This part keeps tracks of all the instances of player in a linked list
 */

// return linked list of players
List *GetPlayerList ()
{
    return (playerList);
}

// update all player controller in instances list
void UpdateAllPlayers ()
{
    Node *currentNode            = playerList -> head;
    Node *nextNode               = NULL;

    while (currentNode          != NULL)
    {
        nextNode                 = currentNode -> next;
        if (currentNode -> data != NULL)
        {
            PlayerUpdate ((Player *) currentNode -> data);
            if (currentNode -> data -> status & DeletionMarkFlag)
            {
                DeconstructPlayer ((Player *) currentNode -> data);
                playerList       = obtain (playerList, currentNode);
                deleteNode (currentNode);
            }
        }
        currentNode              = nextNode;
    }
}

#endif // PLAYER_H 
