#ifndef INPUT_CONTROLLER_MANAGER_C
#define INPUT_CONTROLLER_MANAGER_C
#include "input_controller_manager.h"
#include "../../architecture/component/component_manager.h"
#include "input.h"
#include "input_controller_strategies/input_controller_dispatcher.c"

void ICM_InitializeInputController(InputController* controller)
{
    CM_InitializeComponent((Component*)controller, INPUT_CONTROLLER_COMPONENT);
    ICM_InitializeInput(&controller->input);
    controller->type = INPUT_CONTROLLER_TYPE_GAMEPAD; 
    controller->gamepad = 0;
}

InputController* ICM_ConstructInputController()
{
    InputController* controller = (InputController*)malloc(sizeof(InputController));
    ICM_InitializeInputController(controller);
    return controller;
}

void ICM_DeconstructInputController(InputController* controller)
{
}


void ICM_UpdateInputController(InputController* inputController)
{
    DispatchInputStrategy(inputController);
}

int ICM_InputControllerGet_ValueOfButton(InputController* inputController, GamepadButton button)
{
    switch (button)
    {
    case GAMEPAD_BUTTON_A:
        return inputController->input.buttonA;
        break;
    case GAMEPAD_BUTTON_B:
        return inputController->input.buttonB;
        break;
    case GAMEPAD_BUTTON_X:
        return inputController->input.buttonX;
        break;
    case GAMEPAD_BUTTON_Y:
        return inputController->input.buttonY;
        break;
    case GAMEPAD_BUTTON_L:
        return inputController->input.buttonL;
        break;
    case GAMEPAD_BUTTON_R:
        return inputController->input.buttonR;
        break;
    case GAMEPAD_BUTTON_START:
        return inputController->input.buttonStart;
        break;
    }
}

Vector2* ICM_InputControllerGet_Movement(InputController* inputController)
{
    return &inputController->input.movementDirection;
}

Vector2* ICM_InputControllerGet_NormalizedMovement(InputController* inputController)
{
    return &inputController->input.normalizedMovementDirection;
}

void ICM_InputControllerSet_Gamepad(InputController* controller, int gamepad)
{
    controller->gamepad = gamepad;
}

void ICM_InputControllerSet_Type(InputController* inputController, InputControllerType type)
{
    inputController->type = type;
}

void ICM_InitializeInput(Input* input)
{
    input->buttonA = -1;
    input->buttonB = -1;
    input->buttonX = -1;
    input->buttonY = -1;
    input->buttonL = -1;
    input->buttonR = -1;
    input->buttonStart = -1;
    input->movementDirection.x = 0;
    input->movementDirection.y = 0;
    input->normalizedMovementDirection.x = 0;
    input->normalizedMovementDirection.y = 0;
}

void ICM_DeconstructInput(Input* input)
{

}

#endif //INPUT_CONTRROLLER_MANAGER_H
