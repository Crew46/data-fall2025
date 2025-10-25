#ifndef WEAPON_H
#define WEAPON_H
#include "misc.h"
#include "video.h"
#include "../configuration/region_configurations.h"
#include "../configuration/texture_configurations.h"
#include "../vector/vector2.h"
#include "../object.h"
#include "../data_structures/doubly_linked_list/doubly_linked_list.h"

enum ProjectileType
{
    LASER_TYPE_LASER_CANNON,
    LASER_TYPE_MISSILE_LAUNCHER,
    LASER_TYPE_LIGHTNING_ROD,
};

#include "laser.h"
#include "missile.h"

//initialize instances list
List* weaponList = createList();

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 1: MODEL///////////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

/////////////////////////////////////////////////
///////////1: Struct/////////////////////////////
/////////////////////////////////////////////////

enum WeaponType
{
    WEAPON_TYPE_LASER_CANNON,
    WEAPON_TYPE_MISSILE_LAUNCHER,
    WEAPON_TYPE_LIGHTNING_ROD,
    WEAPON_TYPE_MAGNETIC_ATTRACTION_DEVICE
};

struct Weapon {
    Object object;
    WeaponType type;
    float maxShootCooldownTime; //shoot cooldown in seconds
    float shootCooldownElapsed; //seconds elapsed since last shot
    float lifetime; // Lifetime of the weapon's projectile in seconds
    float despawnTimer;
    bool isFiring;
    int  xOffset;
    int  yOffset;
    bool hasOwner;
};

/////////////////////////////////////////////////
///////////1: Constructor and Deconstructor//////
/////////////////////////////////////////////////

Weapon* CreateWeapon(int textureID, int regionID, int x, int y, int status, WeaponType type, float cooldown, float lifetime)
{
    Weapon* weapon = (Weapon*)malloc(sizeof(Weapon));
    initObject(&weapon->object, Object_Type_Weapon, textureID, regionID, x, y, status);
    weapon->type = type;
    weapon->maxShootCooldownTime = cooldown;
    weapon->shootCooldownElapsed = 0.0;
    weapon->lifetime = lifetime;
    weapon->hasOwner = false;

    weaponList = append(weaponList, weaponList->tail, createNode(&weapon->object));

    int xOffset = -10;
    int yOffset = -5;

    int team = status & TeamFlagMask >> TeamFlagMask;

    if(team      == 0)
    {
        weapon->xOffset =  xOffset;
        weapon->yOffset =  yOffset;
    }
    else if(team == 1)
    {
        weapon->xOffset = -yOffset;
        weapon->yOffset =  xOffset;
    }
    else if(team == 1)
    {
        weapon->xOffset = -xOffset;
        weapon->yOffset = -yOffset;
    }
    else if(team == 1)
    {
        weapon->xOffset =  yOffset;
        weapon->yOffset = -xOffset;
    }

    return weapon;
}

void DeconstructWeapon(Weapon* weapon)
{
    free(weapon);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 2: VISUAL FUNCTIONS////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void DrawWeapon(Weapon* weapon)
{
    drawObject(&weapon->object);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 3: LOGICAL CONNECTION//////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void WeaponShoot(Weapon* weapon)
{
    if(weapon->isFiring)
    {
        //if not in cooldown, shoot
        if(weapon->shootCooldownElapsed <= 0)
        {
            //shoot logic here
            switch (weapon->type)
            {
                case WEAPON_TYPE_LASER_CANNON:
                    CreateLaser(LASER_TEXTURES, LASER_REGION, weapon->object.x, weapon->object.y, weapon->object.status, LASER_TYPE_LASER_CANNON, weapon->lifetime);
                    break;
                case WEAPON_TYPE_MISSILE_LAUNCHER:
                    CreateMissile(LASER_TEXTURES, MISSILE_REGION, weapon->object.x, weapon->object.y, weapon->object.status, LASER_TYPE_MISSILE_LAUNCHER, weapon->lifetime);
                    break;
            }

            // Reset cooldown
            weapon->shootCooldownElapsed = weapon->maxShootCooldownTime;
        }
    }
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 3: LOGICAL CONNECTION//////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void WeaponUpdate(Weapon* weapon)
{
    //logical operations here
    WeaponShoot(weapon);
    weapon -> shootCooldownElapsed  -= 1.0/60.0 * (float)FRAME_SLICES;

    if (weapon -> hasOwner)
    {
        weapon -> despawnTimer       = 7.5;
    }
    else
    {
        weapon -> despawnTimer      -= 1.0/60.0 * (float)FRAME_SLICES;
        if (weapon -> despawnTimer  <  0)
        {
            weapon -> object.status |= DELETION_FLAG;
        }
    }
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 4: INSTANCES MANAGEMENT////////////////////
///////////////////////////////////////////////////////////
//=========================================================

//return linked list of weapons
List* GetWeaponList()
{
    return weaponList;
}

//update all weapon controller in the weapon controller list
void UpdateAllWeapons()
{
    //loop through all instances of weapon controller
    Node* currentNode = weaponList->head;
    Node* nextNode;

    while(currentNode != NULL)
    {
        nextNode = currentNode->next;
        if(currentNode->data != NULL)
        {
            WeaponUpdate((Weapon*)currentNode->data);
            if(currentNode->data->status & DELETION_FLAG)
            {
                DeconstructWeapon((Weapon*)currentNode->data);
                weaponList  = obtain(weaponList, &currentNode);
                deleteNode(currentNode);
            }
        }

        currentNode = nextNode;
    }
}

//deconstruct linked list and all laser controllers in list 
void DeconstructAllWeapons()
{
    //loop through all instances of weapon controller
    Node* currentNode = weaponList->head;
    Node* next;

    while(currentNode != NULL)
    {
        next = currentNode->next;
        DeconstructWeapon((Weapon*)currentNode->data);
        weaponList  = obtain(weaponList, &currentNode);
        deleteNode(currentNode);

        currentNode = next;
    }
}

#endif // WEAPON_H
