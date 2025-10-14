#ifndef VISUALS_H_
#define VISUALS_H_
#include "video.h"

#define BACKGROUND_TEXTURE  0
#define NEBULA_TEXTURE      1
#define PLAYER_TEXTURE		2
#define ENEMYA_TEXTURE		3
#define LASER_TEXTURE		4
#define ENEMYB_TEXTURE		5

#define BACKGROUND_REGION	0
#define NEBULA_REGION    	1
#define PLAYER_REGION		2
#define ENEMYA_REGION		3
#define LASER_REGION		4	
#define ENEMYB_REGION1		5
#define ENEMYB_REGION2		6
#define ENEMYB_REGION3      7

#define LASERSPEED 			1

// Visuals will be used to define textures 
void visuals(void)
{
// Background 
	select_texture (BACKGROUND_TEXTURE);
	select_region (BACKGROUND_REGION);
	define_region_topleft (0, 0, 639, 1024);
// Nebula 
	select_texture (NEBULA_TEXTURE);
	select_region (NEBULA_REGION);
	define_region_topleft (0, 0, 639, 1024);
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
	select_region (ENEMYB_REGION1);
	define_region_center ( 0, 0 , 19, 19);
	select_region (ENEMYB_REGION2);
	define_region_center (0, 21, 19, 39);
	select_region (ENEMYB_REGION3);
	define_region_center (0, 41, 19, 59);
}

Object * updateVisuals(Object * enemy)
{
	if (enemy -> texture    == ENEMYB_TEXTURE)
	{
		if (enemy->hp       == 2)
		{
			enemy->region   = ENEMYB_REGION2;
		}
		if (enemy->hp       == 1)
		{
			enemy->region   = ENEMYB_REGION3;
		}
	}
return(enemy);
}















#endif // VISUALS_H_
