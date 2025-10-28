#ifndef INPUT_CONTROLLER_H
#define INPUT_CONTROLLER_H
#include "../../architecture/component/component.h"

enum InputType
{
    Gamepad,
    CPU 
};

struct InputController
{
    Component* component;
    InputType type;
};

#endif //INPUT_CONTROLLER_H