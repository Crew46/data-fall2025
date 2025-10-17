#ifndef  _REGIONS_CONFIGURATIONS_H
#define  _REGIONS_CONFIGURATIONS_H
#include "texture_configurations.h"
#include "video.h"

/////////////////////////////////////////////////////////////
///////////REGION DEFINITIONS////////////////////////////////
/////////////////////////////////////////////////////////////

#define  BACKGROUND_REGION 0
#define  PLAY_GAME_REGION  2
#define  EXIT_GAME_REGION  3
#define  CREDITS_REGION    4
#define  SETTINGS_REGION   5
#define  WEAPON_REGION     6
#define  LASER_REGION      7
#define  PLAYER_FRAME_0    20
#define  PLAYER_FRAME_1    21
#define  PLAYER_FRAME_2    22
#define  PLAYER_FRAME_3    23
#define  ENEMY_REGION      20 // for now, make same as player just to get something
#define  TITLE_LOGO        30
#define  TITLE_SUBTITLE    31
#define  TITLE_MESSAGE     32
#define  TITLE_START       33
#define  CELESTIAL_LARGE   40
#define  CELESTIAL_MEDIUM  41
#define  CELESTIAL_SMALL   42
#define  STAR0             43
#define  STAR1             44
#define  STAR2             45

void InitializeRegions ()
{
    // Getting the Title Logo
    select_texture (TITLE_TEXTURE);
    select_region (TITLE_LOGO);
    define_region_topleft (0, 45, 420, 75);

    // Getting the Title Subtitle
    select_texture (TITLE_TEXTURE);
    select_region (TITLE_SUBTITLE);
    define_region_topleft (0, 80, 345, 98);

    // Getting the Title Message
    select_texture (TITLE_TEXTURE);
    select_region (TITLE_MESSAGE);
    define_region_topleft (0, 0, 352, 20);

    // Getting the Title Start
    select_texture (TITLE_TEXTURE);
    select_region (TITLE_START);
    define_region_topleft (0, 20, 95, 40);

    // Getting the Background
    select_texture (BACKGROUND_TEXTURE);
    select_region (BACKGROUND_REGION);
    define_region_topleft (0, 0, 639, 359);
    
    // player
    select_texture (PLAYER_TEXTURE);
    select_region (PLAYER_FRAME_0);
    define_region_center (0, 0, 63, 63); // Player sprite
    
    // player
    select_texture (PLAYER_TEXTURE);
    select_region (PLAYER_FRAME_1);
    define_region_center (0, 64, 63, 127); // Player sprite
    
    // player
    select_texture (PLAYER_TEXTURE);
    select_region (PLAYER_FRAME_2);
    define_region_center (0, 128, 63, 191); // Player sprite
    
    // player
    select_texture (PLAYER_TEXTURE);
    select_region (PLAYER_FRAME_3);
    define_region_center (0, 192, 63, 255); // Player sprite

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

    // CELESTIAL_SMALL
    select_texture (CELESTIAL_TEXTURES);
    select_region (CELESTIAL_SMALL);
    define_region_center (130, 25, 155, 60);

    // CELESTIAL_MEDIUM
    select_texture (CELESTIAL_TEXTURES);
    select_region (CELESTIAL_MEDIUM);
    define_region_center (75, 15, 130, 60);

    // CELESTIAL_LARGE
    select_texture (CELESTIAL_TEXTURES);
    select_region (CELESTIAL_LARGE);
    define_region_center (0, 0, 75, 80);

    // STAR0
    select_texture (CELESTIAL_TEXTURES);
    select_region (STAR0);
    define_region_center (30, 110, 43, 120);

    // STAR1
    select_texture (CELESTIAL_TEXTURES);
    select_region (STAR1);
    define_region_center (93, 110, 105, 120);

    // STAR2
    select_texture (CELESTIAL_TEXTURES);
    select_region (STAR2);
    define_region_center (133, 110, 145, 120);
}

#endif // _REGIONS_CONFIGURATIONS_H
