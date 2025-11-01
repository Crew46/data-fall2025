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

void ICM_UpdateInputController(InputController* inputController);

InputController* ICM_ConstructInputController();
void ICM_InitializeInputController(InputController* controller);
void ICM_DeconstructInputController(InputController* controller);

int ICM_InputControllerGet_ValueOfButton(InputController* inputController, GamepadButton button);
Vector2* ICM_InputControllerGet_Movement(InputController* inputController);
Vector2* ICM_InputControllerGet_NormalizedMovement(InputController* inputController);
void ICM_InputControllerSet_Gamepad(InputController* controller, int gamepad);
void ICM_InputControllerSet_Type(InputController* inputController, InputControllerType type);
void ICM_InputControllerSet_DescriptiveData(InputController* controller, InputControllerType type, int gamepad);

void ICM_InitializeInput(Input* input);
void ICM_DeconstructInput(Input* input);

#endif //INPUT_MANAGER_H