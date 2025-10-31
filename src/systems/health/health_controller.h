#ifndef HEALTH_CONTROLLER_H
#define HEALTH_CONTROLLER_H
#include "../../architecture/component/component.h"

struct HealthController
{
   Component component;
   int health; 
   int maxHealth;
   bool inGrace;
   float graceTimeElapsed;
   float maxGraceTime;
};

#endif //HEALTH_CONTROLLER_H