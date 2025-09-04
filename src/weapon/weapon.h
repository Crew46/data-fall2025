#ifndef WEAPON_H
#define WEAPON_H
#include "misc.h"
#include "video.h"
#include "../vector/vector2.h"
#include "../component/component.h"
#include "../data_structures/doubly_linked_list/doubly_linked_list.h"

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
    Component* object;
    WeaponType* type;
    float lifetime; // Lifetime of the weapon's projectile in seconds
};

/////////////////////////////////////////////////
///////////1: Constructor and Deconstructor//////
/////////////////////////////////////////////////

Weapon* CreateWeapon(Component* object, float speed, float lifetime)
{
    Weapon* weapon = (Weapon*)malloc(sizeof(Weapon));
    weapon->object = object;
    weapon->lifetime = lifetime;
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
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 3: LOGICAL CONNECTION//////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void WeaponUpdate(Weapon* weapon)
{
    //logical operations here

    //draw
    DrawWeapon(weapon);
}

//=========================================================
///////////////////////////////////////////////////////////
///////////PART 4: INSTANCES MANAGEMENT////////////////////
///////////////////////////////////////////////////////////
//=========================================================

//initialize instances list
DoublyLinkedList* weaponsList = CreateDoublyLinkedList();

//update all laser controller in the laser controller list
void UpdateAllWeapons()
{
    //loop through all instances of laser controller
    //for(int i = 0; i < instancesOfLaserController; i++)
    //{
        //LaserControllerUpdate();
    //}
}

//deconstruct linked list and all laser controllers in list 
void DeconstructAllWeapons()
{
    //loop through all instances of laser controller
    //for(int i = 0; i < instancesOfLaserController; i++)
    //{
        //DeconstructLaserController();    
    //}
}

#endif // WEAPON_H