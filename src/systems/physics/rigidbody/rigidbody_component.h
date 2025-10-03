#ifndef RIGIDBODY_COMPONENT_H
#define RIGIDBODY_COMPONENT_H
#include "../../../architecture/component/component.h"
#include "../../../vector/vector2.h"

struct RigidbodyComponent
{
    Component base;
    Vector2 velocity; 
    Vector2 acceleration;
    float staticFriction;
    float kineticFriction;
    float mass;
    bool isStatic;
    bool grounded;
    bool hasGravity;
    float restitution; //bounciness factor
    float density; //g/cm^3
};

#endif //RIGIDBODY_COMPONENT_H