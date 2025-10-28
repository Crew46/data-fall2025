#ifndef INPUT_MANAGER_C
#define INPUT_MANAGER_C
#include "input_manager.h"

InputManager* inputManager = NULL;

void InitializeInputManager()
{
    inputManager = (InputManager*)malloc(sizeof(InputManager));
    inputManager->inputControllerList = ConstructDoublyLinkedList();
}

void DeinitializeInputManager()
{

}

void UpdateInputManager()
{
}

InputController* InputManagerConstructInputController()
{

}

void InputManagerDeconstructInputController()
{

}

int InputManagerGetGamepadButtonValueOfInputController(InputController* inputController, GamepadButton button)
{

}

void InputManagerGetMovementOfInputController(InputController* inputController)
{

}

#endif //INPUT_MANAGER_H
