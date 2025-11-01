#ifndef HEALTH_CONTROLLER_MANAGER_H
#define HEALTH_CONTROLLER_MANAGER_H
#include "health_controller.h"


void InitializeHealthController(HealthController* controller);

HealthController* ConstructHealthController();

void DeconstructHealthController(HealthController* controller);

void UpdateHealthController(HealthController* controller);

void HealthControllerDamage(HealthController* controller, int damage);

void HealthControllerHeal(HealthController* controller, int health);

void HealthControllerDie(HealthController* controller);

void HealthControllerRevive(HealthController* controller, int healthToHeal);


//=========================================================
///////////////////////////////////////////////////////////
/////////////GETTERS & SETTERS/////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

int HealthControllerGet_Health(HealthController* controller);

bool HealthControllerGet_InGrace(HealthController* controller);

float HealthControllerGet_GraceTimeElapsed(HealthController* controller);

void HealthControllerSet_MaxGraceTime(HealthController* controller, float maxGraceTime);

float HealthControllerGet_MaxGraceTime(HealthController* controller);

bool HealthControllerGet_IsDead(HealthController* controller);

void HealthControllerSet_DescriptiveData(HealthController* controller, int maxHealth, int maxGraceTime);

#endif //HEALTH_CONTROLLER_MANAGER_H