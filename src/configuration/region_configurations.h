#ifndef  _REGIONS_CONFIGURATIONS_H
#define  _REGIONS_CONFIGURATIONS_H
#include "texture_configurations.h"
#include "video.h"

/////////////////////////////////////////////////////////////
///////////REGION DEFINITIONS////////////////////////////////
/////////////////////////////////////////////////////////////

#define  BACKGROUND_REGION 0
#define  PLAYER_REGION     1
#define  PLAY_GAME_REGION  2
#define  EXIT_GAME_REGION  3
#define  CREDITS_REGION    4
#define  SETTINGS_REGION   5
#define  WEAPON_REGION     6
#define  LASER_REGION      7

void InitializeRegions ()
{
    // Getting the Background
    select_texture (BACKGROUND_TEXTURE);
    select_region (BACKGROUND_REGION);
    define_region_topleft (0, 0, 639, 359);
    
    // player
    select_texture (PLAYER_TEXTURE);
    select_region (PLAYER_REGION);
    define_region_center (0, 0, 31, 31); // Player sprite

    // PLAY
    select_texture (UI_TEXTURES);  
    select_region (PLAY_GAME_REGION);
    define_region_topleft (0, 0, 123, 23);
    
    // EXIT
    select_texture (UI_TEXTURES);  
    select_region (EXIT_GAME_REGION);
    define_region_topleft (0, 24, 107, 47);

    // CREDITS
    select_texture (UI_TEXTURES);  
    select_region (CREDITS_REGION);
    define_region_topleft (0, 48, 191, 71);

    // WEAPON
    select_texture (WEAPON_TEXTURES );
    select_region (WEAPON_REGION);
    define_region_center (0, 0, 9, 19);

    //LASER
    select_texture (LASER_TEXTURES);
    select_region (LASER_REGION);
    define_region_center (0, 0, 9, 19);
}

#endif // _REGIONS_CONFIGURATIONS_H
