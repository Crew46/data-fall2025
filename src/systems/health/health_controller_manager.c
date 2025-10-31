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
    print_at(screen_width / 2, screen_height - 20, "updating health");
}

void HealthControllerDamage(HealthController* controller, int damage)
{
}

void HealthControllerHeal(HealthController* controller, int health)
{

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

void HealthControllerSet_Health(HealthController* controller, int health)
{
    controller->health = health;
}

bool HealthControllerGet_InGrace(HealthController* controller)
{
    return controller->inGrace;
}

void HealthControllerSet_InGrace(HealthController* controller, bool inGrace)
{
    controller->inGrace = inGrace;
}

float HealthControllerGet_GraceTimeElapsed(HealthController* controller)
{
    return controller->graceTimeElapsed;
}

void HealthControllerSet_GraceTimeElapsed(HealthController* controller, float time)
{
    controller->graceTimeElapsed = time;
}

float HealthControllerGet_MaxGraceTime(HealthController* controller)
{
    return controller->maxGraceTime;
}

void HealthControllerSet_MaxGraceTime(HealthController* controller, float maxGraceTime)
{
    controller->maxGraceTime = maxGraceTime;
}

#endif //HEALTH_CONTROLLER_MANAGER_C