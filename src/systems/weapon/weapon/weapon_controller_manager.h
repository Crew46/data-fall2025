#ifndef WEAPON_CONTROLLER_MANAGER_H
#define WEAPON_CONTROLLER_MANAGER_H
#include "weapon_controller.h"

void WCM_WeaponControllerInitialize(WeaponController* controller);
WeaponController* WCM_WeaponControllerConstruct();
void WCM_WeaponControllerDeconstruct(WeaponController* controller);

//=========================================================
///////////////////////////////////////////////////////////
/////////////GETTERS & SETTERS/////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void WCM_WeaponControllerSet_WeaponType(WeaponController* controller, WeaponType type);

WeaponType WCM_WeaponControllerGet_WeaponType(WeaponController* controller);

void WCM_WeaponControllerSet_DescriptiveData(WeaponController* controller, WeaponType type);

#endif //WEAPON_CONTROLLER_MANAGER_H