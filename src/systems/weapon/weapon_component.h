#ifndef WEAPON_COMPONENT_H
#define WEAPON_COMPONENT_H
#include "../../architecture/component/component.h"

enum WeaponType
{
    WEAPON_TYPE_LASER_CANNON,
    WEAPON_TYPE_MISSILE_LAUNCHER,
    WEAPON_TYPE_LIGHTNING_ROD,
    WEAPON_TYPE_MAGNETIC_ATTRACTION_DEVICE
};

struct WeaponComponent {
    Component base;
    WeaponType type;
};

#endif // WEAPON_COMPONENT_H