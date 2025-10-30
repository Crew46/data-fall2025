#ifndef INPUT_CONTROLLER_MANAGER_H
#define INPUT_CONTROLLER_MANAGER_H
#include "../../data_structures/doubly_linked_list/doubly_linked_list.h"
#include "../../vector/vector2.h"
#include "input_controller.h"

enum GamepadButton
{
    GAMEPAD_BUTTON_A,
    GAMEPAD_BUTTON_B,
    GAMEPAD_BUTTON_X,
    GAMEPAD_BUTTON_Y,
    GAMEPAD_BUTTON_L,
    GAMEPAD_BUTTON_R,
    GAMEPAD_BUTTON_START
};


void InitializeInputManager();
void DeinitializeInputManager();

void InputManagerUpdateInputController(InputController* inputController);

InputController* InputManagerConstructInputController();
void InputManagerInitializeInputController(InputController* controller);
void InputManagerDeconstructInputController(InputController* controller);

int InputManagerGetButtonValueOfInputController(InputController* inputController, GamepadButton button);
Vector2* InputManagerGetMovementOfInputController(InputController* inputController);
Vector2* InputManagerGetNormalizedMovementOfInputController(InputController* inputController);
void InputManagerSetInputControllerGamepad(InputController* controller, int gamepad);
void InputManagerSetInputControllerType(InputController* inputController, InputControllerType type);

void InputManagerInitializeInput(Input* input);
void InputManagerDeconstructInput(Input* input);

#endif //INPUT_MANAGER_H