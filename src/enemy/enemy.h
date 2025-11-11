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
    bool    status             = false;
    Node   *dropped            = dequeue (enemy -> weapons);
    Weapon *wtmp               = NULL;

    if (dropped               != NULL)
    {
        wtmp                   = ((Weapon *) dropped -> data);
        wtmp -> hasOwner       = false;
        wtmp -> isFiring       = false;
        wtmp -> object.dy      = 380;
        wtmp -> object.vy      = 1;
        free (dropped);
        dropped                = NULL;
        status                 = true;
    }

    return (status);
}

void enemyGrabWeapon (Enemy *enemy)
{
    int     newStatus                        = 0;
    int     tmpStatus                        = 0;
    Node   *currentNode                      = GetWeaponList() -> head;
    Weapon *weapon                           = NULL;

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

                    enemy  -> weaponIndexer  = enemy -> weaponIndexer + 1;
                    enemy  -> weaponIndexer  = enemy -> weaponIndexer % 3;
                }
            }
        }

        currentNode                          = currentNode -> next;
    }
}

void setEnemyWeaponPositions (Enemy *enemy)
{
    int     team                   = 0;
    Node   *currentNode            = enemy -> weapons -> data -> head;
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
    Node   *currentNode            = enemy -> weapons -> data -> head;
    Weapon *currentWeapon          = NULL;

    if (canFire)
    {
        fireStatus                 = ((rand() % 10) >  5);
    }

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
    int     bestDistance             = 0;
    int     tmp                      = 0;
    bool    isBest                   = false;

    while (currentNode              != NULL)
    {
        if (currentNode -> data     != NULL)
        {
            if (currentNode -> data != NULL)
            {
                tmp                  = abs (enemy -> object.x - currentNode -> data -> x);
                isBest               = false;

                if (bestTarget      == NULL)
                {
                    isBest           = true;
                }
                else if (tmp        <  bestDistance)
                {
                    isBest           = true;
                }

                if (((currentNode -> data -> status ^ enemy -> object.status) & TeamFlagMask) == 0)
                {
                    isBest           = false;
                }


                if(isBest)
                {
                    bestTarget       = currentNode -> data;
                    bestDistance     = tmp;
                }
            }
        }
        currentNode                  = currentNode -> next;
    }

    enemy -> target                  = bestTarget;
}

void enemyAI (Enemy *enemy)
{
    int pick                              = rand () % 24;
    if (enemy -> object.y                <  20)
    {
        enemy -> object.dy                = 2;
    }
    else if (enemy -> object.y           >  200)
    {
        enemy -> object.dy                = -2;
    }
    else if (pick                        >  21)
    {
        enemy -> object.dy                = 0;
    }
    else if (pick                        >  20)
    {
        enemy -> object.dy                = 2;
    }
    else if (pick                        >  18)
    {
        enemy -> object.dy                = 1;
    }
    else if (pick                        >  16)
    {
        enemy -> object.dy                = -1;
    }

    enemyFindTarget (enemy);

    if(enemy -> target                   != NULL)
    {
        Object *target                    = enemy -> target;
        if (! (target -> status & DELETION_FLAG))
        {
            enemy -> object.dx            = target -> x - enemy -> object.x;

            //Set speed
            if (abs (enemy -> object.dx) <  FRAME_SLICES)
            {
                enemy -> object.dx        = 0;
            }
            else
            {
                enemy -> object.dx        = min (enemy -> object.dx,  enemy -> object.vx);
                enemy -> object.dx        = max (enemy -> object.dx, -enemy -> object.vx);
            }

            //Set firing and rush attack
            int distance                  = abs (enemy -> object.x - enemy -> target -> x);
            if (distance                 <  10)
            {
                enemyFireWeapons (enemy, true);
                if (pick                 <  10 &&
                    enemy -> object.x    <  250)
                {
                    enemy -> object.dy    = 3;
                }
            }
            else
            {
                enemyFireWeapons (enemy, false);
            }
        }
    }
}

void EnemyCheckProjectiles (Enemy* enemy, List* projectiles)
{
    int   damage            = 0;
    Node *currentNode       = projectiles -> head;

    while (currentNode     != NULL)
    {
        if (((currentNode -> data -> status ^ enemy -> object.status) & TeamFlagMask) != 0)
        {
            if (collisionCheck (&enemy -> object, currentNode -> data))
            {
                damage      = 1;
                if (currentNode -> data -> type == Object_Type_Missile)
                {
                    damage  = 0;
                    ((Missile *) currentNode -> data)->explode = true;
                }
                else if(currentNode -> data -> type == Object_Type_Explosion)
                {
                    damage = ((Explosion *) currentNode -> data)->damage;
                }

                if(enemy -> invincTimer <= 0.0 && damage != 0)
                {
                    enemy -> invincTimer = 1.0;
                    enemy -> health -= damage;
                }

                if(enemy -> health <= 0)
                {
                    enemy -> object.status |= DELETION_FLAG;
                }


            }
        }

        currentNode         = currentNode -> next;
    }
}
void EnemyUpdate (Enemy *enemy)
{
    if (enemy -> object.status & IS_ACTIVE_FLAG)
    {
        enemyAI (enemy);
        moveEnemy (enemy);
        setEnemyWeaponPositions (enemy);
    }

    enemy -> invincTimer -= 1.0 / 60.0 * (float)FRAME_SLICES;

    EnemyCheckProjectiles (enemy, GetLaserList     ());
    EnemyCheckProjectiles (enemy, GetMissileList   ());
    EnemyCheckProjectiles (enemy, GetExplosionList ());
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 4: CONSTRUCTION////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

//constructor
Enemy *CreateEnemy (int textureID, int *regions, int num_regions, int x, int y, int status, float maxShootCooldownTime, bool addToList)
{
    int [1] tmpregion;
    // allocate memory for enemy
    Enemy  *enemy            = (Enemy *) malloc (sizeof (Enemy));
    Weapon *weapon           = NULL;

    // enemy object properties initialization
    initObject (&enemy -> object, Object_Type_Entity, textureID, regions, num_regions, x, y, status);

    enemy -> object.dy       = 1;
    enemy -> weapons         = createQueue (3);

    int pick                 = rand () % 20;
    if(pick == 0)
    {
        tmpregion[0]         = LAUNCHER_REGION;
        weapon               = CreateWeapon (WEAPON_TEXTURES, tmpregion, 1, enemy->object.x, enemy->object.y, status, WEAPON_TYPE_MISSILE_LAUNCHER, maxShootCooldownTime, 2.0);
    }
    else
    {
        tmpregion[0]         = WEAPON_REGION;
        weapon               = CreateWeapon (WEAPON_TEXTURES, tmpregion, 1, enemy->object.x, enemy->object.y, status, WEAPON_TYPE_LASER_CANNON, maxShootCooldownTime, 2.0);
    }

    enqueue (enemy -> weapons, createNode (&weapon -> object));
    weapon -> hasOwner       = true;

    enemy -> weaponIndexer   = 1;
    enemy  -> health         = 3;
    enemy  -> maxHealth      = 3;
    enemy  -> invincTimer    = 0.0;


    if(addToList)
    {
        enemyList            = append (enemyList, enemyList -> tail, createNode (&enemy -> object));
    }

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
    Node *currentNode                  = enemy -> weapons -> data -> head;

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
        enemyList       = obtain (enemyList, &currentNode);
        deleteNode (currentNode);

        currentNode     = currentNode -> next;
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
