#ifndef PLAYER_VIEW_H 
#define PLAYER_VIEW_H
#include "player_model.h"

//=========================================================
///////////////////////////////////////////////////////////
///////////////PLAYER VIEW ////////////////////////////////
///////////////////////////////////////////////////////////
//=========================================================

/** 
 * SUMMARY:
 * this file is for visualizing the data of the player model
**/

void DrawPlayerView(PlayerModel* player)
{
    select_texture(player->object.textureID);
    select_region(player->object.regionID);
    draw_region_at(player->object.x, player->object.y);
}

#endif //PLAYER_MODEL_H