#ifndef WEAPON_SELECTION_CONTROLLER_H
#define WEAPON_SELECTION_CONTROLLER_H
#include "../weapon/weapon_controller.h"
#include "../../../data_structures/doubly_linked_list/doubly_linked_list.h"
#include "../../../architecture/component/component.h"

struct WeaponSelectionController
{
    Component component;
    WeaponController* selectedWeapon;
    //queue replacement when ready
    DoublyLinkedList* weaponsList;
};

#endif //WEAPON_SELECTION_CONTROLLER_H