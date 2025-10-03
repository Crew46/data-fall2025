#ifndef RIGIDBODY_MANAGER_H
#define RIGIDBODY_MANAGER_H
#include "rigidbody_component.h"

void CalculateResultantForce(RigidbodyComponent* rigidBody, Vector2* forceOut);

#endif //RIGIDBODY_MANAGER_H