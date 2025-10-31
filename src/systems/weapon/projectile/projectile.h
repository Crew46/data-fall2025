#ifndef PROJECTILE_H
#define PROJECTILE_H
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

#endif //PROJECTILE_H