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
#include "../player/player.h"
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
    Object* target;
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

bool enemyDropWeapon (Enemy *enemy)
{
    Node *dropped              = dequeue (enemy -> weapons);
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

void enemyGrabWeapon (Enemy *enemy)
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

        currentNode                          = currentNode -> next;
    }
}

void setEnemyWeaponPositions (Enemy *enemy)
{
    int     team                   = 0;
    Node   *currentNode            = enemy -> weapons -> list -> head;
    Weapon *currentWeapon          = NULL;

    team                           = (enemy -> object.status & TeamFlagMask);
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

        currentWeapon -> object.x  = enemy -> object.x + realX;
        currentWeapon -> object.y  = enemy -> object.y + realY;

        currentNode                = currentNode -> next;
    }
}

void enemyFireWeapons (Enemy *enemy, bool canFire)
{
    bool    fireStatus             = canFire;

    if(canFire)
    {
        fireStatus             = ((rand() % 10) >  5);
    }

    Node   *currentNode            = enemy -> weapons -> list -> head;
    Weapon *currentWeapon          = NULL;

    while (currentNode            != NULL)
    {
        currentWeapon              = (Weapon *) currentNode -> data;
        currentWeapon -> isFiring  = fireStatus;
        currentNode                = currentNode -> next;
    }
}

void enemyFindTarget (Enemy *enemy)
{
    Node   *currentNode              = playerList -> head;
    Object *bestTarget               = NULL;
    int     bestDistance;
    int     tmp;
    bool    isBest;

    while (currentNode              != NULL)
    {
        if (currentNode -> data     != NULL)
        {
            if (currentNode -> data != NULL)
            {
                tmp                  = abs(enemy->object.x - currentNode->data->x);
                isBest               = false;

                if (bestTarget      == NULL)
                {
                    isBest           = true;
                }
                else if (tmp         < bestDistance)
                {
                    isBest           = true;
                }

                if (((currentNode -> data -> status ^ enemy -> object.status) & TeamFlagMask) == 0)
                {
                    isBest           = false;
                }


                if(isBest)
                {
                    bestTarget       = currentNode->data;
                    bestDistance     = tmp;
                }
            }
        }
        currentNode                  = currentNode -> next;
    }

    enemy -> target                  = bestTarget;

    if(bestDistance                  < 10)
    {
        enemyFireWeapons(enemy, true);
    }
    else
    {
        enemyFireWeapons(enemy, false);
    }
}

void enemyAI (Enemy *enemy)
{
    int  pick                             = 0;

    enemyFindTarget (enemy);

    if(enemy -> target                   != NULL)
    {
        Object *target                    = enemy -> target;
        if (! (target -> status & DELETION_FLAG))
        {
            enemy -> object.dx            = target -> x - enemy -> object.x;
            if (abs (enemy -> object.dx) <  FRAME_SLICES)
            {
                enemy -> object.dx        = 0;
            }
            else
            {
                enemy -> object.dx = min (enemy -> object.dx,  enemy -> object.vx);
                enemy -> object.dx = max (enemy -> object.dx, -enemy -> object.vx);
            }
        }
    }

    pick                                  = rand () % 24;
    if (pick                             >  20)
    {    
        enemy -> object.dy = 0;
    }
    else if (pick                        >  12)
    {
        enemy -> object.dy = 2;
    }
    else
    {
        enemy -> object.dy = 1;
    }
}

void EnemyUpdate (Enemy *enemy)
{
    List *lasers        = GetLaserList ();
    Node *currentNode   = lasers -> head;

    if (enemy -> object.status & IS_ACTIVE_FLAG)
    {
        enemyAI (enemy);
        moveEnemy (enemy);
        setEnemyWeaponPositions (enemy);
    }

    while (currentNode != NULL)
    {
        if (((currentNode -> data -> status ^ enemy -> object.status) & TeamFlagMask) != 0)
        {
            if (collisionCheck (&enemy -> object, currentNode -> data))
            {
                enemy -> object.status |= DELETION_FLAG;
            }
        }

        currentNode                     = currentNode -> next;
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
    Enemy  *enemy            = (Enemy *) malloc (sizeof (Enemy));
    Weapon *weapon           = NULL;

    // enemy object properties initialization
    initObject (&enemy -> object, Object_Type_Entity, textureID, regionID, x, y, status);

    enemy -> object.dy       = 1;
    enemy -> weapons         = createQueue (3);
    weapon                   = CreateWeapon (WEAPON_TEXTURES, WEAPON_REGION, enemy->object.x, enemy->object.y, status, WEAPON_TYPE_LASER_CANNON, maxShootCooldownTime, 2.0);
    enqueue (enemy -> weapons, createNode (&weapon -> object));
    weapon -> hasOwner       = true;

    enemy -> weaponIndexer   = 1;

    enemyList                = append (enemyList, enemyList -> tail, createNode (&enemy -> object));

    // return pointer to enemy
    return (enemy);
}

// deconstructor
void DeconstructEnemy (Enemy *enemy)
{
    while(enemyDropWeapon(enemy));

    free (enemy);
    enemy                       = NULL;
}

void DeconstructEnemyAndWeapon (Enemy *enemy)
{
    Node *currentNode                  = enemy -> weapons -> list -> head;

    while (currentNode                != NULL)
    {
        currentNode -> data -> status |= DELETION_FLAG;
        currentNode                    = currentNode -> next;
    }

    DeconstructEnemy (enemy);
}

void DeconstructAllEnemies ()
{
    // loop through all instances of enemys
    Node *currentNode   = enemyList -> head;

    while (currentNode != NULL)
    {
        DeconstructEnemy ((Enemy *) currentNode -> data);
        enemyList      = obtain (enemyList, &currentNode);
        deleteNode (currentNode);

        currentNode     = currentNode -> start;
    }
}

void DeconstructAllEnemiesAndWeapons ()
{
    // loop through all instances of enemys
    Node *currentNode   = enemyList -> head;

    while (currentNode != NULL)
    {
        DeconstructEnemyAndWeapon ((Enemy *) currentNode -> data);
        enemyList      = obtain (enemyList, &currentNode);
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

    while (currentNode          != NULL)
    {
        if (currentNode -> data != NULL)
        {
            EnemyUpdate ((Enemy *) currentNode -> data);

            if (currentNode -> data -> status & DELETION_FLAG)
            {
                DeconstructEnemy ((Enemy *) currentNode -> data);
                enemyList       = obtain (enemyList, &currentNode);
                deleteNode (currentNode);
            }
        }
        currentNode              = currentNode -> next;
    }
}

#endif // _ENEMY_H 
