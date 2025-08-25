#ifndef REGIONS_CONFIGURATIONS_H
#define REGIONS_CONFIGURATIONS_H
#include "textures_configurations.h"
#include "video.h"

/////////////////////////////////////////////////////////////
///////////REGION DEFINITIONS////////////////////////////////
/////////////////////////////////////////////////////////////

#define BACKGROUND_REGION 0
#define REGION_PLAYER 1

void InitializeRegions()
{
    // Getting the Background
    select_texture( BACKGROUND_TEXTURE );
    select_region ( BACKGROUND_REGION );
    define_region_topleft( 0,0, 639,359);
    
    //player
    select_texture(PLAYER_SPRITES_TEXTURE);
    select_region(REGION_PLAYER);
    define_region(0, 0, 31, 31, 0, 0); // Player sprite

}

#endif //REGIONS_CONFIGURATIONS_H