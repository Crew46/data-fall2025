#ifndef WEAPON_SELECTION_CONTROLLER_MANAGER_C
#define WEAPON_SELECTION_CONTROLLER_MANAGER_C
#include "weapon_selection_controller_manager.h"
#include "../../../architecture/game_object/game_object_manager.h"

void WSCM_WeaponSelectionController_Initialize(WeaponSelectionController* controller)
{
    CM_InitializeComponent((Component*)controller, WEAPON_SELECTION_CONTROLLER);
    controller->selectedWeapon = NULL;
    WSCM_WeaponSelectionController_UpdateWeaponsList(controller);
}

WeaponSelectionController* WSCM_WeaponSelectionController_Construct()
{

}

void WSCM_WeaponSelectionController_Deconstruct(WeaponSelectionController* controller)
{

}

void WSCM_WeaponSelectionController_Update(WeaponSelectionController* controller)
{

}

void WSCM_WeaponSelectionController_UpdateWeaponsList(WeaponSelectionController* controller)
{
    GOM_GameObjectGet_ComponentsByType(controller->component.gameObjectAttatchedTo, WEAPON_CONTROLLER_COMPONENT, &controller->weaponsList);
}

#endif //WEAPON_SELECTION_CONTROLLER_MANAGER_C