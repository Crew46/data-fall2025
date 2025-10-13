#ifndef _ENEMY_H
#define _ENEMY_H
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
 * the enemy, including:
 *
 * part 1: the model
 * part 2: visual functions
 * part 3: logical connections between model and view
 * part 4: instance management
 * part 5: construction and desconstruction
 *
 */

// declarations

List *enemyList  = createList();

struct Enemy 
{
    // object is not a pointer, in order to embed to struct for upcasting & downcasting.
    Object  object;
    Queue  *weapons; // weapon that enemy has equipped
    int     weaponIndexer;
};

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 1: PLAYER MODEL////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

/*
 * SUMMARY:
 * This is the model of the enemy: ie. the fundamental 
 * behaviors of the enemy. logical connection between these functions is in part 3
 */

// move enemy in a direction, where then direction is scaled by the enemy's speed
void moveEnemy (Enemy *enemy)
{
    moveObject (&enemy -> object);
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

void DrawEnemy (Enemy *enemy)
{
    drawObject (&enemy -> object);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 3: LOGICAL CONNECTION//////////////////////
///////////////////////////////////////////////////////////
//=========================================================

/*
 * SUMMARY:
 * This part is the glue to making the enemy model, enemy 
 * view, and input work together. ie the logic that connects 
 * the enemy's model, view, and input.
 */

void enemyDropWeapon (Enemy *enemy)
{
    Node *dropped              = dequeue (enemy -> weapons);
    if (dropped               != NULL)
    {
        ((Weapon *) dropped -> data) -> hasOwner = false;
        free (dropped);
        dropped                = NULL;

        // accessing dropped after free() is just asking for trouble
    }
}

void enemyGrabWeapon (Enemy *enemy)
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
            if (collisionCheck (&enemy -> object, currentNode -> data))
            {
                if (enqueue (enemy -> weapons, createNode (currentNode -> data)))
                {
                    newStatus                = weapon -> object.status;
                    newStatus                = newStatus & (~TeamFlagMask);
                    tmpStatus                = enemy -> object.status & TeamFlagMask;
                    newStatus                = newStatus | tmpStatus;

                    weapon -> object.status  = newStatus;
                    weapon -> hasOwner       = true;

                    weapon -> yOffset        = -5;
                    weapon -> xOffset        = -10 + (10 * enemy -> weaponIndexer);

                    enemy -> weaponIndexer  = enemy -> weaponIndexer + 1;
                    enemy -> weaponIndexer  = enemy -> weaponIndexer % 3;
                }
            }
        }

        currentNode                          = nextNode;
    }
}

void enemyFireWeapons (Enemy *enemy)
{
    bool    fireStatus             = ((rand() % 10) >  5);

    Node   *currentNode            = enemy -> weapons -> list -> head;
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

void EnemyUpdate (Enemy *enemy)
{
    List *lasers        = GetLaserList ();
    Node *currentNode   = lasers -> head;
    Node *nextNode      = NULL;

    if (enemy -> object.status & IsActiveFlag)
    {
        // Update the enemy view every frame
        DrawEnemy (enemy);
    }

    while (currentNode != NULL)
    {
        nextNode        = currentNode -> next;

        if (((currentNode -> data -> status ^ enemy -> object.status) & TeamFlagMask) != 0)
        {
            if (collisionCheck (&enemy -> object, currentNode -> data))
            {
                enemy -> object.status |= DeletionMarkFlag;
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
Enemy *CreateEnemy (int textureID, int regionID, int x, int y, int status, float maxShootCooldownTime)
{
    // allocate memory for enemy
    Enemy *enemy           = (Enemy *) malloc (sizeof (Enemy));
    Weapon *weapon           = NULL;

    // enemy object properties initialization
    initObject (&enemy -> object, Object_Type_Entity, textureID, regionID, x, y, status);

    enemy -> weapons        = createQueue (3);
    weapon                   = CreateWeapon (WEAPON_TEXTURES, WEAPON_REGION, enemy->object.x, enemy->object.y, status, WEAPON_TYPE_LASER_CANNON, maxShootCooldownTime, 2.0);
    enqueue (enemy -> weapons, createNode (&weapon -> object));
    weapon -> hasOwner       = true;

    enemy -> weaponIndexer  = 1;

    append (enemyList, enemyList -> tail, createNode (&enemy -> object));

    // return pointer to enemy
    return (enemy);
}

// deconstructor
void DeconstructEnemy (Enemy *enemy)
{
    Node *currentNode            = dequeue (enemy -> weapons);

    while (currentNode          != NULL)
    {
        if (currentNode -> data != NULL)
        {
            ((Weapon *) currentNode -> data) -> hasOwner  = false;
        }
        currentNode              = dequeue (enemy -> weapons);
    }

    free (enemy);
    enemy                       = NULL;
}

void DeconstructEnemyAndWeapon (Enemy *enemy)
{
    Node *currentNode                  = enemy -> weapons -> list -> head;
    Node *nextNode                     = NULL;

    while (currentNode                != NULL)
    {
        nextNode                       = currentNode -> next;

        currentNode -> data -> status |= DeletionMarkFlag;

        currentNode                    = nextNode;
    }

    DeconstructEnemy (enemy);
}

void DeconstructAllEnemies ()
{
    // loop through all instances of enemys
    Node *currentNode   = enemyList -> head;
    Node *next          = NULL;

    while (currentNode != NULL)
    {
        next            = currentNode -> next;
        DeconstructEnemy ((Enemy *) currentNode -> data);
        enemyList      = obtain (enemyList, currentNode);
        deleteNode (currentNode);

        currentNode     = next;
    }
}

void DeconstructAllEnemiesAndWeapons ()
{
    // loop through all instances of enemys
    Node *currentNode   = enemyList -> head;
    Node *next          = NULL;

    while (currentNode != NULL)
    {
        next            = currentNode -> next;
        DeconstructEnemyAndWeapon ((Enemy *) currentNode -> data);
        enemyList      = obtain (enemyList, currentNode);
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
 * This part keeps tracks of all the instances of enemy in a linked list
 */

// return linked list of enemys
List *GetEnemyList ()
{
    return (enemyList);
}

// update all enemy controller in instances list
void UpdateAllEnemies ()
{
    Node *currentNode            = enemyList -> head;
    Node *nextNode               = NULL;

    while (currentNode          != NULL)
    {
        nextNode                 = currentNode -> next;
        if (currentNode -> data != NULL)
        {
            EnemyUpdate ((Enemy *) currentNode -> data);
            if (currentNode -> data -> status & DeletionMarkFlag)
            {
                DeconstructEnemy ((Enemy *) currentNode -> data);
                enemyList       = obtain (enemyList, currentNode);
                deleteNode (currentNode);
            }
        }
        currentNode              = nextNode;
    }
}

#endif // _ENEMY_H 
