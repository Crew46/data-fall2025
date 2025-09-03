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
 * this part is for visualizing the data of the model
**/

void DrawPlayer(PlayerModel* player)
{
    select_texture(player->object.textureID);
    select_region(player->object.regionID);
    draw_region_at(player->object.x, player->object.y);
}


void Create

#endif //PLAYER_MODEL_H