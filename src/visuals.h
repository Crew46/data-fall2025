#ifndef VISUALS_H_
#define VISUALS_H_
#include "video.h"

#define BACKGROUND_TEXTURE  0
#define PLAYER_TEXTURE		1
#define ENEMYA_TEXTURE		2
#define LASER_TEXTURE		3
#define ENEMYB_TEXTURE		4

#define BACKGROUND_REGION	0
#define PLAYER_REGION		1
#define ENEMYA_REGION		2
#define LASER_REGION		3	
#define ENEMYB_REGION		4

#define LASERSPEED 			1

// Visuals will be used to define textures 
void visuals(void)
{
// Background 
	select_texture (BACKGROUND_TEXTURE);
	select_region (BACKGROUND_REGION);
	define_region_topleft (0, 0, 639, 359);
// Player
	select_texture (PLAYER_TEXTURE);
	select_region (PLAYER_REGION);
	define_region_center (0, 0, 31, 31);
//EnemyA
	select_texture (ENEMYA_TEXTURE);
	select_region (ENEMYA_REGION);
	define_region_center (0, 0 , 9, 9 );
// Player laser
	select_texture (LASER_TEXTURE);
	select_region (LASER_REGION);
	define_region_center (0 ,0 , 19, 9);
//EnemyB
	select_texture (ENEMYB_TEXTURE);
	select_region  (ENEMYB_REGION);
	define_region_center ( 0, 0 , 19, 19);
}


















#endif
