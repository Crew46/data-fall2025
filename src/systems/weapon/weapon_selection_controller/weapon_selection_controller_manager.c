#ifndef WEAPON_SELECTION_CONTROLLER_MANAGER_C
#define WEAPON_SELECTION_CONTROLLER_MANAGER_C
#include "weapon_selection_controller_manager.h"
#include "../../../architecture/game_object/game_object_manager.h"
#include "../../../architecture/component/component_manager.h"
#include "../weapon/weapon_controller_manager.h"

void WSCM_WeaponSelectionController_Initialize(WeaponSelectionController* controller)
{
    CM_InitializeComponent((Component*)controller, WEAPON_SELECTION_CONTROLLER);
    controller->selectedWeapon = NULL;
    WSCM_WeaponSelectionController_UpdateWeaponsList(controller);
}

WeaponSelectionController* WSCM_WeaponSelectionController_Construct()
{
    WeaponSelectionController* controller = (WeaponSelectionController*)malloc(sizeof(WeaponSelectionController));
    WSCM_WeaponSelectionController_Initialize(controller);
    return controller;
}

void WSCM_WeaponSelectionController_Deconstruct(WeaponSelectionController* controller)
{
    DeconstructDoublyLinkedList(controller->weaponsList);
    WCM_WeaponControllerDeconstruct(controller->selectedWeapon);
    CM_DeconstructComponent(&controller->component);
    free(controller);
}

void WSCM_WeaponSelectionController_Update(WeaponSelectionController* controller)
{
}

void WSCM_WeaponSelectionController_UpdateWeaponsList(WeaponSelectionController* controller)
{
    GOM_GameObjectGet_ComponentsByType(controller->component.gameObjectAttatchedTo, WEAPON_CONTROLLER_COMPONENT, &controller->weaponsList);
}

WeaponController* WSCM_WeaponSelectionController_SelectWeapon(WeaponSelectionController* controller, WeaponController* weaponController)
{
}

WeaponController* WSCM_WeaponSelectionController_SelectNextWeapon()
{

}

void WSCM_ShootSelectedWeapon(WeaponSelectionController* controller)
{
    WCM_WeaponController_Shoot(controller->selectedWeapon);
}

#endif //WEAPON_SELECTION_CONTROLLER_MANAGER_C