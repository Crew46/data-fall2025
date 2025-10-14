#ifndef _GAME_CONFIGURATIONS_H
#define _GAME_CONFIGURATIONS_H

//=========================================================
///////////////////////////////////////////////////////////
///////////DECLARATIONS////////////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

enum GameState
{
    GAMESTATE_INTRO,
    GAMESTATE_TITLE,
    GAMESTATE_MENU,
    GAMESTATE_INGAME,
    GAMESTATE_PLAYAGAIN,
    GAMESTATE_CREDITS,
    GAMESTATE_DEMO
};

GameState  currentState;

#endif // _GAME_CONFIGURATIONS_H
