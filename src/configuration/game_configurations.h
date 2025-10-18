#ifndef _GAME_CONFIGURATIONS_H
#define _GAME_CONFIGURATIONS_H

////////////////////////////////////////////////////////////////////////////////////////
//
// GameState struct: used for tracking current game state
//
enum GameState
{
    GAMESTATE_INTRO,        // pre-title screen intro
    GAMESTATE_TITLE,        // title screen
    GAMESTATE_MENU,         // menu
    GAMESTATE_GAMEPLAY,     // gameplay
    GAMESTATE_PAUSE,        // pause
    GAMESTATE_PLAYAGAIN,    // prompt to play again
    GAMESTATE_CREDITS,      // credit sequence
    GAMESTATE_DEMO          // demo mode
};

////////////////////////////////////////////////////////////////////////////////////////
//
// Global variable declarations
//
GameState  currentState;    // tracking current game state
int        half_seconds;    // tracking half-seconds that have transpired
int        max_obj_vy;      // maximum allowable Y velocity (for objects)
int        min_obj_vy;      // minimum allowable Y velocity (for objects)
int        vy_obj_factor;   // Y velocity multiplication factor (for objects)

#endif // _GAME_CONFIGURATIONS_H
