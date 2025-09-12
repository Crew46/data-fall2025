#ifndef PROJECTILE_COMPONENT_H
#define PROJECTILE_COMPONENT_H struct 
#include "../../architecture/component/component.h"

enum ProjectileComponentType
{
    PROJECTILE_TYPE_ROCKET,
    PROJECTILE_TYPE_LASER
};

struct ProjectileComponent
{
    Component component;
    ProjectileComponentType type;
};

#endif //PROJECTILE_COMPONENT_H