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

void HealthControllerSet_Health(HealthController* controller, int health);

int HealthControllerGet_Health(HealthController* controller);

void HealthControllerSet_InGrace(HealthController* controller, bool inGrace);

bool HealthControllerGet_InGrace(HealthController* controller);

void HealthControllerSet_GraceTimeElapsed(HealthController* controller, float time);

float HealthControllerGet_GraceTimeElapsed(HealthController* controller);

void HealthControllerSet_MaxGraceTime(HealthController* controller, float maxGraceTime);

float HealthControllerGet_MaxGraceTime(HealthController* controller);

bool HealthControllerGet_IsDead(HealthController* controller);

#endif //HEALTH_CONTROLLER_MANAGER_H