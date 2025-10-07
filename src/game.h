#ifndef GAME_H // game.h
#define GAME_H

// Vircon Libraries
#include "input.h"
#include "misc.h"
#include "video.h"
#include "time.h"

// Textures, Regions, and constants(for now)
#define  BACKGROUND_TEXTURE 0
#define  PLAYER_TEXTURE     1
#define  ENEMY_TEXTURE      2
#define  LASER_TEXTURE      3

#define  BACKGROUND_REGION  0
#define  PLAYER_REGION      1
#define  ENEMY_REGION       2
#define  LASER_REGION       3

#define  SCREEN_WIDTH       640
#define  SCREEN_HEIGHT      360

#define  ENEMY_WIDTH        10
#define  ENEMY_HEIGHT       10
#define  LASER_WIDTH        3
#define  LASER_HEIGHT       10

// Declare structs here to avoid compiler errors
struct Object;
struct Node;
struct DoublyLinkedList;
struct Stack;
struct Queue;
struct Laser;
struct Weapon;
struct Entity;

// Header files
#include "object.h"
#include "node.h"
#include "list.h"
#include "stack.h"
#include "queue.h"
#include "laser.h"
#include "weapon.h"
#include "entity.h"


void updateGame(Entity* player, DoublyLinkedList* enemyList, DoublyLinkedList* ammoList)
{

  player = updatePlayer( player );
  ammoList = updateAmmo(ammoList);
  enemyList = updateEnemies( enemyList );

  checkAmmoCollisionWithEnemies(&ammoList, &enemyList);
}

void renderGame(Entity* player, DoublyLinkedList* enemyList, DoublyLinkedList* ammoList )
{
  renderPlayer(player);
  renderEnemies(enemyList);
  renderAmmo(ammoList);
}

void drawBackground(int textureID, int regionID)
{
  select_texture ( textureID );
  select_region ( regionID );
  draw_region_at ( 0, 0 );
}

void defineTextures()
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Define the background texture and region
    //
    select_texture ( BACKGROUND_TEXTURE );
    select_region ( BACKGROUND_REGION );
    define_region_topleft ( 0, 0, 639, 359 );

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Define the player texture and region
    //
    select_texture ( PLAYER_TEXTURE );
    select_region ( PLAYER_REGION );
    define_region ( 0, 0, 31, 31, 0, 0 );

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Define the enemy texture and region
    //
    select_texture( ENEMY_TEXTURE );
    select_region( ENEMY_REGION );
    define_region_topleft( 0, 0, 10, 10 );

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Define the laser texture and region
    //
    select_texture( LASER_TEXTURE );
    select_region( LASER_REGION );
    define_region_topleft( 0, 0, 3, 10 );
}


#endif
