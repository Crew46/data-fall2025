#ifndef WEAPON_CONTROLLER_H
#define WEAPON_CONTROLLER_H
#include "../../architecture/component/component.h"

enum WeaponType
{
    WEAPON_TYPE_LASER_CANNON,
    WEAPON_TYPE_MISSILE_LAUNCHER,
    WEAPON_TYPE_LIGHTNING_ARC,
    WEAPON_TYPE_MAGNETIC_ATTRACTION_DEVICE
};

struct WeaponController {
    Component base;
    WeaponType type;
};

#endif // WEAPON_CONTROLLER_H