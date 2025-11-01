#ifndef WEAPON_CONTROLLER_MANAGER_C
#define WEAPON_CONTROLLER_MANAGER_C
#include "weapon_controller_manager.h"
#include "../../../architecture/component/component_manager.h"
#include "strategies/weapon_controller_strategy_dispatcher.c"

void WCM_WeaponControllerInitialize(WeaponController* controller)
{
    CM_InitializeComponent((Component*)controller, WEAPON_CONTROLLER_COMPONENT);
    WCM_WeaponControllerSet_DescriptiveData(controller, WEAPON_CONTROLLER_TYPE_LASER_CANNON);
}

WeaponController* WCM_WeaponControllerConstruct()
{
    WeaponController* controller = (WeaponController*)malloc(sizeof(WeaponController)); 
    WCM_WeaponControllerInitialize(controller);
    return controller;
}

void WCM_WeaponControllerDeconstruct(WeaponController* controller)
{

}

//=========================================================
///////////////////////////////////////////////////////////
/////////////GETTERS & SETTERS/////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

void WCM_WeaponControllerSet_WeaponType(WeaponController* controller, WeaponType type)
{
    controller->type = type;
}

WeaponType WCM_WeaponControllerGet_WeaponType(WeaponController* controller)
{
    return controller->type;
}

void WCM_WeaponControllerSet_DescriptiveData(WeaponController* controller, WeaponType type)
{
    controller->type = type;
}

#endif //WEAPON_CONTROLLER_MANAGER_C