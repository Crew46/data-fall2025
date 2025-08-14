#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "input.h"
#include "misc.h"
#include "string.h"
#include "time.h"
#include "video.h"

struct Gamemanager {
};

GameManager* CreateGameManager();

void InitializeGameManager(GameManager* gameManager);

void UpdateGameManager(Gamemanager* gameManager);

#endif
