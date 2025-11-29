#ifndef VISUALS_H_
#define VISUALS_H_
#include "video.h"

// Textures
#define BACKGROUND_TEXTURE  		0
#define NEBULA_TEXTURE      		1
#define PLAYER_TEXTURE				2
#define ENEMYA_TEXTURE				3
#define LASER_TEXTURE				4
#define ENEMYB_TEXTURE				5
#define SHIELD_TEXTURE 				6
#define EXPLOSION_TEXTURE   		7
#define ROCKET_TEXTURE      		8
#define BOSSA_TEXTURE				9
#define PAWNA_TEXTURE 				10
#define ENEMYC_TEXTURE				11
#define ENEMYLASER_TEXTURE  		12
#define ROCKETEXPLOSION_TEXTURE     13
// Regions
#define BACKGROUND_REGION			0
#define NEBULA_REGION    			1
#define PLAYER_REGION				2
#define ENEMYA_REGION				3
#define LASER_REGION				4		
#define ENEMYB_REGION1				5
#define ENEMYB_REGION2				6
#define ENEMYB_REGION3      		7
#define SHIELD_REGION				8
#define PLAYERSHIELD_REGION 		9
#define EXPLOSION_REGION    		10
#define ROCKET_REGION      			11
#define BOSSA_REGION				12	
#define PAWNA_REGION				13
#define ENEMYC_REGION				14
#define ENEMYLASER_REGION			15
#define ROCKETEXPLOSION_REGION		16
#define LASERSPEED 					1

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
// Player and player shield
	select_texture (PLAYER_TEXTURE);
	select_region (PLAYER_REGION);
	define_region_center (0, 0, 31, 31);
	select_region (PLAYERSHIELD_REGION);
	define_region_center (0, 32, 31, 63 );
//EnemyA
	select_texture (ENEMYA_TEXTURE);
	select_region (ENEMYA_REGION);
	define_region_center (0, 0 , 9, 9 );
//laser ammo
	select_texture (LASER_TEXTURE);
	select_region (LASER_REGION);
	define_region_center (0 ,0 , 3, 9);
//EnemyB
	select_texture (ENEMYB_TEXTURE);
	select_region (ENEMYB_REGION1);
	define_region_center ( 0, 0 , 19, 19);
	select_region (ENEMYB_REGION2);
	define_region_center (0, 20, 19, 39);
	select_region (ENEMYB_REGION3);
	define_region_center (0, 40, 19, 59);
// Shield Powerup
	select_texture (SHIELD_TEXTURE);
	select_region (SHIELD_REGION);
	define_region_center (0, 0, 11, 11);
// Explosion
	select_texture ( EXPLOSION_TEXTURE);
	select_region ( EXPLOSION_REGION);
	define_region_center (0, 0, 19, 19);
// Rocket ammo
	select_texture ( ROCKET_TEXTURE);
	select_region ( ROCKET_REGION);
	define_region_center (0, 0, 11, 11);
// BossA 
	select_texture ( BOSSA_TEXTURE);
	select_region (BOSSA_REGION);
	define_region_center (0, 0, 99, 99 );
// PawnA
	select_texture ( PAWNA_TEXTURE);
	select_region ( PAWNA_REGION);
	define_region_center (0, 0, 29, 29);
// EnemyC
	select_texture ( ENEMYC_TEXTURE);
	select_region ( ENEMYC_REGION);
	define_region_center (0, 0, 19, 19);
// Enemy Laser
	select_texture ( ENEMYLASER_TEXTURE);
	select_region ( ENEMYLASER_REGION);
	define_region_center (0, 0, 3, 9);
//	Rocket Explosion
	select_texture ( ROCKETEXPLOSION_TEXTURE);
	select_region ( ROCKETEXPLOSION_REGION);
	define_region_center (0,0, 61, 61);
}

Object * updateVisuals(Object * enemy)
{
	if (enemy -> texture    == ENEMYB_TEXTURE)
	{
		if (enemy->hp       == 4 || enemy -> hp == 3)
		{
			enemy->region   = ENEMYB_REGION2;
		}
		if (enemy->hp       == 2 || enemy -> hp == 1)
		{
			enemy->region   = ENEMYB_REGION3;
		}
	}
return(enemy);
}



	











#endif // VISUALS_H_
