#ifndef INPUT_CONTROLLER_MANAGER_C
#define INPUT_CONTROLLER_MANAGER_C
#include "input_controller_manager.h"
#include "../../architecture/component/component_manager.h"
#include "input.h"
#include "input_controller_dispatcher.c"

InputManager* inputManager = NULL;

void InitializeInputManager()
{
    inputManager = (InputManager*)malloc(sizeof(InputManager));
    inputManager->inputControllerList = ConstructDoublyLinkedList();
}

void DeinitializeInputManager()
{

}

void InputManagerInitializeInputController(InputController* controller)
{
    CM_InitializeComponent((Component*)controller, INPUT_CONTROLLER_COMPONENT);
    InputManagerInitializeInput(&controller->input);
    DoublyLinkedListInsertElementToTail(inputManager->inputControllerList, (Object*)controller);
    controller->type = INPUT_CONTROLLER_TYPE_GAMEPAD; 
    controller->gamepad = 0;
}

InputController* InputManagerConstructInputController()
{
    InputController* controller = (InputController*)malloc(sizeof(InputController));
    InputManagerInitializeInputController(controller);
    return controller;
}

void InputManagerDeconstructInputController(InputController* controller)
{
}


void InputManagerUpdateInputController(InputController* inputController)
{
    print_at(screen_width / 2, screen_height / 2, "UPDATING");
    DispatchInputStrategy(inputController);
}

int InputManagerGetButtonValueOfInputController(InputController* inputController, GamepadButton button)
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

Vector2* InputManagerGetMovementOfInputController(InputController* inputController)
{
    return &inputController->input.movementDirection;
}

void InputManagerSetInputControllerGamepad(InputController* controller, int gamepad)
{
    controller->gamepad = gamepad;
}

void InputManagerSetInputControllerType(InputController* inputController, InputControllerType type)
{
    inputController->type = type;
}

void InputManagerInitializeInput(Input* input)
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
}

void InputManagerDeconstructInput(Input* input)
{

}

#endif //INPUT_CONTRROLLER_MANAGER_H
