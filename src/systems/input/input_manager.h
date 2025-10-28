#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H
#include "../../data_structures/doubly_linked_list/doubly_linked_list.h"
#include "../../vector/vector2.h"
#include "input_controller.h"

struct InputManager
{
    DoublyLinkedList* inputControllerList;
};

enum GamepadButton
{
    A,
    B,
    X,
    Y,
    L,
    R,
    START
};

void InitializeInputManager();
void DeinitializeInputManager();

void UpdateInputManager();

InputController* InputManagerConstructInputController();
void InputManagerDeconstructInputController();

int InputManagerGetGamepadButtonValueOfInputController(InputController* inputController, GamepadButton button);
void InputManagerGetMovementOfInputController(InputController* inputController);
void InputManagerSetInputControllerGamepad(InputController* inputController);
void InputManagerSetInputControllerInputType(InputType type);

#endif //INPUT_MANAGER_H