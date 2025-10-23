#ifndef _PLAYER_H
#define _PLAYER_H

// Vircon32 standard libraries
#include "input.h"
#include "math.h"
#include "misc.h"
#include "video.h"

// project custom libraries
#include "../object.h"
#include "../data_structures/doubly_linked_list/doubly_linked_list.h"
#include "../data_structures/queue/queue.h"
#include "../weapon/weapon.h"
#include "../tools/debugger.h"

////////////////////////////////////////////////////////////////////////////////////////
//
// player.h: player-related functionality for use in the game
//
// part 1: the model API
//
//         void movePlayer (Player *player);
//
// part 2: visual functions API
//
//         void DrawPlayer (Player *player);
//
// part 3: logical connections between model and view API
//
//         void playerDropWeapon         (Player *player);
//         void playerGrabWeapon         (Player *player);
//         void setPlayerWeaponPositions (Player *player);
//         void playerFireWeapons        (Player *player);
//         void HandleInput              (Player *player);
//         void PlayerUpdate             (Player *player);
//
// part 4: instance management API
//
//         Player *CreatePlayer (int textureID, int regionID,
//                               int x,         int y,
//                               int status,    float maxShootCooldownTime,
//                               int gamepadID);
//         void    DeconstructPlayer               (Player *player);
//         void    DeconstructPlayerAndWeapon      (Player *player);
//         void    DeconstructAllPlayers           (void);
//         void    DeconstructAllPlayersAndWeapons (void);
//
// part 5: construction and desconstruction API
//
//         List *GetPlayerList   (void);
//         void  UpdateAllPlayers (void);
//
////////////////////////////////////////////////////////////////////////////////////////


#define JUST_PLAYER   0
#define NOT_WEAPON    0
#define ALL_PLAYERS   1
#define PLAYER_WEAPON 2
#define ALL_WEAPONS   4

#define MAXWEAPONS 3

// declarations

List *playerList  = createList();

struct Player 
{
    // object is not a pointer, in order to embed to struct for upcasting & downcasting.
    Object  object;
    int     gamepadID;
    Queue  *weapons; // weapon that player has equipped
    int     weaponIndexer;
    int     health;
    int     maxHealth;
    float   invincTimer;
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

bool playerDropWeapon (Player *player)
{
    Node *dropped              = dequeue (player -> weapons);
    if (dropped               != NULL)
    {
        ((Weapon *) dropped -> data) -> hasOwner = false;
        ((Weapon *) dropped -> data) -> isFiring = false;
        free (dropped);
        dropped                = NULL;

        return true;
    }

    return false;
}

void playerGrabWeapon (Player *player)
{
    Node   *currentNode                      = GetWeaponList() -> head;
    Weapon *weapon                           = NULL;
    int     newStatus                        = 0;
    int     tmpStatus                        = 0;

    while (currentNode                      != NULL)
    {
        weapon                               = (Weapon *) currentNode -> data;

        if(weapon -> hasOwner               == false)
        {
            if (collisionCheck (&player -> object, currentNode -> data))
            {
                if (enqueue (player -> weapons, createNode (currentNode -> data)))
                {
                    newStatus                = weapon -> object.status;
                    tmpStatus                = TeamFlagMask;
                    newStatus                = newStatus & (~tmpStatus);
                    tmpStatus                = player -> object.status & TeamFlagMask;
                    newStatus                = newStatus | tmpStatus;

                    weapon -> object.status  = newStatus;
                    weapon -> hasOwner       = true;

                    weapon -> yOffset        = -5;
                    weapon -> xOffset        = -10 + (10 * player -> weaponIndexer);

                    player -> weaponIndexer  = player -> weaponIndexer + 1;
                    player -> weaponIndexer  = player -> weaponIndexer % MAXWEAPONS;
                }
            }
        }

        currentNode                          = currentNode -> next;
    }
}

void setPlayerWeaponPositions (Player *player)
{
    int     team                   = 0;
    Node   *currentNode            = player -> weapons -> list -> head;
    Weapon *currentWeapon          = NULL;

    team                           = (player -> object.status & TeamFlagMask);
    team                           = team >> TeamFlagOffset;

    while (currentNode            != NULL)
    {
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

        currentNode                = currentNode -> next;
    }
}

void playerFireWeapons (Player *player)
{
    bool    fireStatus             = (gamepad_button_a () >  0);
    Node   *currentNode            = player -> weapons -> list -> head;
    Weapon *currentWeapon          = NULL;

    while (currentNode            != NULL)
    {
        currentWeapon              = (Weapon *) currentNode -> data;
        currentWeapon -> isFiring  = fireStatus;
        currentNode                = currentNode -> next;
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
        if ((gamepad_button_b () % 30 <= 29) &&
            (gamepad_button_b () % 30 >= 30-FRAME_SLICES))
        {
            playerDropWeapon (player);
        }

        setPlayerWeaponPositions (player);
        playerFireWeapons (player);
    }

    if ((gamepad_button_b ()           >= 1) &&
        (gamepad_button_b ()           <= FRAME_SLICES))
    {
        playerGrabWeapon (player);
    }
}

void PlayerUpdate (Player *player)
{
    List *lasers        = GetLaserList ();
    Node *currentNode   = lasers -> head;

    if (player -> object.status & IS_ACTIVE_FLAG)
    {
        //handle input every frame
        HandleInput (player);
    }

    player -> invincTimer -= 1.0 / 60.0 * (float)FRAME_SLICES;

    while (currentNode != NULL)
    {
        if (((currentNode -> data -> status ^ player -> object.status) & TeamFlagMask) != 0)
        {
            if (collisionCheck (&player -> object, currentNode -> data))
            {
                if(player -> invincTimer <= 0.0)
                {
                    player -> invincTimer = 1.0;
                    player -> health--;
                }

                if(player -> health <= 0)
                {
                    player -> object.status |= DELETION_FLAG;
                }
            }
        }

        currentNode     = currentNode -> next;
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

    player -> weapons        = createQueue (MAXWEAPONS);
    weapon                   = CreateWeapon (WEAPON_TEXTURES,
                                             WEAPON_REGION,
                                             player -> object.x,
                                             player -> object.y,
                                             status,
                                             WEAPON_TYPE_LASER_CANNON,
                                             maxShootCooldownTime,
                                             2.0);

    enqueue (player -> weapons, createNode (&weapon -> object));
    weapon -> hasOwner       = true;

    player -> weaponIndexer  = 1;

    append (playerList, playerList -> tail, createNode (&player -> object));

    player -> health         = 3;
    player -> maxHealth      = 3;
    player ->invincTimer     = 0.0;

    // return pointer to player
    return player;
}

// deconstructor
void DeconstructPlayer (Player *player, int status)
{
    bool    just_player           = true;
    bool    all_players           = false;
    bool    player_weapon         = false;
    bool    all_weapons           = false;
    Node   *currentNode           = NULL;
    Object *otmp                  = NULL;
    Weapon *wtmp                  = NULL;

    if ((status & ALL_PLAYERS)   == ALL_PLAYERS) 
    {
        all_players               = true;
        currentNode               = playerList -> head;
        just_player               = false;

        while (currentNode       != NULL)
        {
            DeconstructPlayer ((Player *) currentNode -> data, JUST_PLAYER | NOT_WEAPON);
            playerList            = obtain (playerList, &currentNode);
            deleteNode (currentNode);

            currentNode           = currentNode -> next;
        }
    }

    if ((status & PLAYER_WEAPON) == PLAYER_WEAPON) 
    {
        currentNode               = player -> weapons -> list -> head;
        player_weapon             = true;
        while (currentNode       != NULL)
        {
            otmp                  = currentNode -> data;
            otmp -> status        = otmp -> status | DELETION_FLAG;
            currentNode           = currentNode -> next;
        }
    }

    if ((status & ALL_WEAPONS)   == ALL_WEAPONS) 
    {
        all_weapons               = true;
        player_weapon             = false;
    }

    currentNode                   = dequeue (player -> weapons);
    while (currentNode           != NULL)
    {
        if (currentNode -> data  != NULL)
        {
            wtmp                  = (Weapon *) currentNode -> data;
            wtmp -> hasOwner      = false;
        }
        currentNode               = dequeue (player -> weapons);
    }

    free (player);
    player                        = NULL;
}

void DeconstructPlayerAndWeapon (Player *player)
{
    Node *currentNode                  = player -> weapons -> list -> head;

    while (currentNode                != NULL)
    {
        currentNode -> data -> status |= DELETION_FLAG;
        currentNode                    = currentNode -> next;
    }

    DeconstructPlayer (player, JUST_PLAYER | PLAYER_WEAPON);
}

void DeconstructAllPlayers ()
{
    // loop through all instances of players
    Node *currentNode   = playerList -> head;

    while (currentNode != NULL)
    {
        DeconstructPlayer ((Player *) currentNode -> data, ALL_PLAYERS);
        playerList      = obtain (playerList, &currentNode);
        deleteNode (currentNode);

        currentNode     = currentNode -> next;
    }
}

void DeconstructAllPlayersAndWeapons ()
{
    // loop through all instances of players
    Node *currentNode   = playerList -> head;

    while (currentNode != NULL)
    {
        DeconstructPlayerAndWeapon ((Player *) currentNode -> data);
        playerList      = obtain (playerList, &currentNode);
        deleteNode (currentNode);

        currentNode     = currentNode -> next;
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

    while (currentNode          != NULL)
    {
        if (currentNode -> data != NULL)
        {
            PlayerUpdate ((Player *) currentNode -> data);
            if (currentNode -> data -> status & DELETION_FLAG)
            {
                DeconstructPlayer ((Player *) currentNode -> data, JUST_PLAYER);
                playerList       = obtain (playerList, &currentNode);
                deleteNode (currentNode);
            }
        }
        currentNode              = currentNode -> next;
    }
}

#endif // _PLAYER_H 
