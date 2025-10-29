#ifndef WEAPON_H // weapon.h
#define WEAPON_H

struct Object;
struct DoublyLinkedList;
///////////////////////////////////////////////////////////////////////
//
// WeaponType enum and Weapon structure
//
enum WeaponType
{
  Weapon_Type_None,
  Weapon_Type_Laser,
};

struct Weapon
{
  WeaponType weaponType;
  DoublyLinkedList* ammoList;
};

Weapon* createWeapon(WeaponType wType)
{
  Weapon* weapon = (Weapon*)malloc(sizeof(Weapon));
  weapon->weaponType = wType;
  weapon->ammoList = createList();
  return weapon;
}

#endif
