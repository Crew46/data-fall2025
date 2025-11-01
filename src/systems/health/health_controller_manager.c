#ifndef HEALTH_CONTROLLER_MANAGER_C
#define HEALTH_CONTROLLER_MANAGER_C
#include "health_controller_manager.h"
#include "../../architecture/component/component_manager.h"
#include "video.h"

void InitializeHealthController(HealthController* controller)
{
    CM_InitializeComponent((Component*)controller, HEALTH_CONTROLLER_COMPONENT);
    controller->maxHealth = 100;
    controller->health = controller->maxHealth;
    controller->inGrace = false;
    controller->graceTimeElapsed = 0;
    controller->maxGraceTime = 1; 
}

HealthController* ConstructHealthController()
{
    HealthController* controller = (HealthController*)malloc(sizeof(HealthController));
    InitializeHealthController(controller);
    return controller;
}

void DeconstructHealthController(HealthController* controller)
{

}

void UpdateHealthController(HealthController* controller)
{
}

void HealthControllerDamage(HealthController* controller, int damage)
{
    if(damage >= controller->health)
    {
        HealthControllerDie(controller);
    }
    else
    {
        controller->health = controller->health - damage;
    }
}

void HealthControllerHeal(HealthController* controller, int health)
{
    controller->health = health;
}

void HealthControllerDie(HealthController* controller)
{
    controller->health = 0;
}

void HealthControllerRevive(HealthController* controller, int healthToHeal)
{
    HealthControllerHeal(controller, healthToHeal);
}

//=========================================================
///////////////////////////////////////////////////////////
/////////////GETTERS & SETTERS/////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

int HealthControllerGet_Health(HealthController* controller)
{
    return controller->health;
}

bool HealthControllerGet_InGrace(HealthController* controller)
{
    return controller->inGrace;
}

float HealthControllerGet_GraceTimeElapsed(HealthController* controller)
{
    return controller->graceTimeElapsed;
}

float HealthControllerGet_MaxGraceTime(HealthController* controller)
{
    return controller->maxGraceTime;
}

void HealthControllerSet_MaxGraceTime(HealthController* controller, float maxGraceTime)
{
    controller->maxGraceTime = maxGraceTime;
}

bool HealthControllerGet_IsDead(HealthController* controller)
{
    if(controller->health == 0)
    {
        return true;
    }
}

void HealthControllerSet_DescriptiveData(HealthController* controller, int maxHealth, int maxGraceTime)
{
    controller->maxHealth = maxHealth;
    controller->maxGraceTime = maxGraceTime;
}

#endif //HEALTH_CONTROLLER_MANAGER_C