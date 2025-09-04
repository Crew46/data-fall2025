#ifndef COLLIDER_H
#define COLLIDER_H
#include "../component_based_architecture/component/component_manager.h"

struct Collider
{
    Component base;
}

void InitializeCollider(Collider* collider, int* name)
{
    //initialize component base
    ComponentManagerInitializeComponent(collider->base, name, COLLIDER_COMPONENT);
}

void DeconstructCollider()
{

}

#endif // COLLIDER_H
