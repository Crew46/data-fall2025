#ifndef INPUT_CONTROLLER_H
#define INPUT_CONTROLLER_H
#include "../../architecture/component/component.h"
#include "input.h"

enum InputControllerType
{
    INPUT_CONTROLLER_TYPE_GAMEPAD,
    INPUT_CONTROLLER_TYPE_SHIP_CPU
};
 
struct InputController
{
    Component component;
    Input input;
    InputControllerType type;
    int gamepad;
};

#endif //INPUT_CONTROLLER_H