#include "game.h"

void main(void)
{
  ////////////////////////////////////////////////////////////////////////////////////
  //
  // Seed the rng
  //
  srand( get_time() );

  ////////////////////////////////////////////////////////////////////////////////////
  //
  // Create our player instance
  //
  int xPos        = 360;
  int yPos        = 300;
  bool isActive   = true;
  Entity* player = createEntity( PLAYER_TEXTURE, PLAYER_REGION, xPos, yPos, isActive, Weapon_Type_Laser );
  player->obj.vx = 3; // Set manually for now
  player->obj.vy = 1;

  ////////////////////////////////////////////////////////////////////////////////////
  //
  // Create enemy list
  // 
  DoublyLinkedList* enemyList = createList();
  for(int i = 0; i < 5; ++i) // Add 5 enemies to start
  {
    int  xPos     = rand() % 630;
    int  yPos     = 0;
    bool isActive = true;
    Entity* enemy = createEntity( ENEMY_TEXTURE, ENEMY_REGION, xPos, yPos, isActive, Weapon_Type_Laser );

    enemyList = append(enemyList, enemyList->tail, &enemy->obj);
  }

  /////////////////////////////////////////////////////////////////////////////////////
  //
  // Set up and define textures
  //
  defineTextures();

  ////////////////////////////////////////////////////////////////////////////////////
  //
  // Select the first gamepad
  //
  select_gamepad (0);

  ////////////////////////////////////////////////////////////////////////////////////
  //
  // Game loop
  //
  while (true)
  {
    //clear screen -- do we really need this?
    clear_screen (color_white);

    // Draw Background
    drawBackground( BACKGROUND_TEXTURE, BACKGROUND_REGION );

    // Update Game
    updateGame(player, enemyList, player->weapon->ammoList);

    // Render Game
    renderGame(player, enemyList, player->weapon->ammoList);

    // End frame
    end_frame();
  }

  // Free our list and all its contents
  deleteList( &enemyList );
}
