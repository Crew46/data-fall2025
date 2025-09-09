#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H
#include "player_model.h"
#include "../../architecture/component/component.h"

struct PlayerController 
{
    Component base;
    PlayerModel* playerModel;
};

#endif //PLAYER_CONTROLLER_H