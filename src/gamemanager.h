#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "input.h"
#include "misc.h"
#include "string.h"
#include "time.h"
#include "video.h"

enum GameState
{
    Menu
};

struct GameManager {
    GameState gameState;
};

GameManager* CreateGameManager();

void InitializeGameManager(GameManager* gameManager);

void UpdateGameManager(GameManager* gameManager);

void DeinitializeGameManager(GameManager* gameManager);

#endif
