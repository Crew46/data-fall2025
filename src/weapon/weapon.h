#ifndef WEAPON_H
#define WEAPON_H
#include "misc.h"
#include "video.h"
#include "../configuration/region_configurations.h"
#include "../configuration/texture_configurations.h"
#include "../vector/vector2.h"
#include "../object.h"
#include "../data_structures/doubly_linked_list/doubly_linked_list.h"
#include "laser.h"

//initialize instances list
DoublyLinkedList* weaponsList = CreateDoublyLinkedList();

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
    bool isFiring;
};

/////////////////////////////////////////////////
///////////1: Constructor and Deconstructor//////
/////////////////////////////////////////////////

Weapon* CreateWeapon(int* name, int textureID, int regionID, int id, int x, int y, bool isActive, int speed, WeaponType type, float cooldown, float lifetime)
{
    Weapon* weapon = (Weapon*)malloc(sizeof(Weapon));
    InitializeObject(&weapon->object, name, textureID, regionID, id, x, y, isActive, speed);
    weapon->type = type;
    weapon->maxShootCooldownTime = cooldown;
    weapon->shootCooldownElapsed = 0.0;
    weapon->lifetime = lifetime;

    DoublyLinkedListInsertAtTail(weaponsList, &weapon->object);

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
    DrawObject(&weapon->object);
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
            CreateLaser("laser", LASER_TEXTURES, LASER_REGION, 0, weapon->object.x, weapon->object.y, true, 10, LASER_TYPE_LASER_CANNON, weapon->lifetime);

            // Reset cooldown
            weapon->shootCooldownElapsed = weapon->maxShootCooldownTime;
        }
    }
}

void WeaponUpdate(Weapon* weapon)
{
    //logical operations here
    WeaponShoot(weapon);
    weapon->shootCooldownElapsed -= 1.0/60.0;

    //draw
    DrawWeapon(weapon);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 4: INSTANCES MANAGEMENT////////////////////
///////////////////////////////////////////////////////////
//=========================================================

//return linked list of weapons
DoublyLinkedList* GetWeaponList()
{
    return weaponsList;
}

//update all weapon controller in the weapon controller list
void UpdateAllWeapons()
{
    //loop through all instances of weapon controller
    DoublyNode* currentNode = weaponsList->head;

    while(currentNode != NULL)
    {
        WeaponUpdate((Weapon*)currentNode->data);

        currentNode = currentNode->next;
    }
}

//deconstruct linked list and all laser controllers in list 
void DeconstructAllWeapons()
{
    //loop through all instances of weapon controller
    DoublyNode* currentNode = weaponsList->head;

    while(currentNode != NULL)
    {
        DeconstructWeapon((Weapon*)currentNode->data);
        DoublyLinkedListDeleteNode(weaponsList, currentNode);

        currentNode = currentNode->next;
    }
}

#endif // WEAPON_H