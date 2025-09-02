#include "input.h"
#include "misc.h"
#include "video.h"
#include "time.h"

#define  BACKGROUND_TEXTURE 0
#define  PLAYER_TEXTURE     1
#define  ENEMY_TEXTURE      2

#define  BACKGROUND_REGION  0
#define  PLAYER_REGION      1
#define  ENEMY_REGION       2

#define  SCREEN_WIDTH       640
#define  SCREEN_HEIGHT      360

#define  ENEMY_WIDTH         10
#define  ENEMY_HEIGHT        10

////////////////////////////////////////////////////////////////////////////////////
//
//  Object struct and helpers
//
struct Object
{
    int     textureID;
    int     regionID;
    int     id;
    int     x;
    int     y;
    int     xdir;
    int     ydir;
    bool    isActive;
    int     speed;
    Object  *next;
};

Object* createObject(int textureID, int regionID, int xPos, int yPos, bool isActive, Object* next)
{
  Object* obj = (Object*)malloc(sizeof(Object));
  obj->textureID = textureID;
  obj->regionID = regionID;
  obj->x = xPos;
  obj->y = yPos;
  obj->isActive = isActive;
  obj->next = next;

  return obj;
}

Object* deleteObject(Object** obj)
{
  free(*obj);
  *obj = NULL;
}


////////////////////////////////////////////////////////////////////////////////////
//
//  Node struct and helpers
//
struct Node
{
  Object* data;
  Node* next;
  Node* prev;
};

Node* createNode(Object* data)
{
  Node* node = (Node*)malloc(sizeof(Node));
  node->data = data;
  node->next = NULL;
  node->prev = NULL;

  return node;
}



////////////////////////////////////////////////////////////////////////////////////
//
//  Linked List struct and helpers
//
struct DoublyLinkedList
{
  Node* head;
  Node* tail;
};

DoublyLinkedList* deleteNode(DoublyLinkedList* list, Node** node)
{
  if(!list || !node || !*node)
    return list;

  // Only one node
  if(list->head == (*node) && list->tail == (*node))
  {
    list->head = NULL;
    list->tail = NULL;
  }
  else if(*node == list->head)
  {
    list->head = (*node)->next;
    list->head->prev = NULL;
  }
  else if(*node == list->tail)
  {
    list->tail = (*node)->prev;
    list->tail->next = NULL;
  }
  else
  {
    (*node)->next->prev = (*node)->prev;
    (*node)->prev->next = (*node)->next;
  }

  free(*node);
  *node = NULL;

  return list;
}

DoublyLinkedList* createList()
{
  DoublyLinkedList* list = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
  list->head = NULL;
  list->tail = NULL;

  return list;
}

void deleteList(DoublyLinkedList** list)
{
  Node* current = (*list)->head;
  while(current != NULL)
  {
    Node* next = current->next;
    deleteNode((*list), &current);
    current = next;
  }
  free(*list);
  *list = NULL;
}

DoublyLinkedList* addFront(DoublyLinkedList* list, Object* data)
{
  Node* node = createNode(data);
  if(list->head == NULL)
  {
    list->head = node;
    list->tail = node;
  }
  else
  {
    list->head->prev = node;
    node->next = list->head;
    list->head = node;
  }

  return list;
}

DoublyLinkedList* addBack(DoublyLinkedList* list, Object* data)
{
  Node* node = createNode(data);
  if(list->head == NULL)
  {
   list->head = node;
   list->tail = node;
  }
  else
  {
    list->tail->next = node;
    node->prev = list->tail;
    list->tail = node;
  }

  return list;

}

// Checks bounds but should only be used for objects that don't need to check which side they are exceeding
bool exceedsBounds(Object* obj)
{
  if(obj->x < 0 || obj->x > SCREEN_WIDTH)
    return true;
  if(obj->y < 0 || obj->y > SCREEN_HEIGHT)
    return true;

  return false;
}

void moveObject(Object* obj, int xdir, int ydir)
{
  obj  -> xdir   = xdir;
  obj  -> ydir   = ydir; 
  obj  -> x      = obj  -> x + obj  -> xdir;
  obj  -> y      = obj  -> y + obj  -> ydir;
}
void drawObject(Object* obj)
{
  select_texture ( obj->textureID );
  select_region  ( obj->regionID );
  draw_region_at ( obj->x, obj->y );
}
void checkObjectCollision(Object* objA, Object* objB, int objA_Width, int objB_Width, int objA_Height, int objB_Height)
{
  // Check if objects are NULL
  if(!objA || !objB)
    return;

  // Make collision less sensitive
  int cushion = 2;

  int aLeft   = objA->x + cushion;
  int aRight  = objA->x + objA_Width - cushion;
  int aTop    = objA->y + cushion;
  int aBottom = objA->y + objA_Height - cushion;

  int bLeft   = objB->x;
  int bRight  = objB->x + objB_Width;
  int bTop    = objB->y;
  int bBottom = objB->y + objB_Height;


  if( aLeft <= bRight 
      && aRight >= bLeft 
      && aBottom >= bTop 
      && aTop <= bBottom) {

    print_at(300, 120, "COLLISION");
  }
}

DoublyLinkedList* spawnEnemy(DoublyLinkedList* list, int xPos, int yPos)
{
  Object* enemy = createObject( ENEMY_TEXTURE, ENEMY_REGION, xPos, yPos, true, NULL );
  list = addBack( list, enemy );

  return list;

}

DoublyLinkedList* updateEnemies(DoublyLinkedList* enemyList)
{
  Node*   current = enemyList->head;
  Node*   next    = NULL;
  Object* enemy   = NULL;

  while(current != NULL)
  {
    next  = current->next;
    enemy = current->data;
    
    for(Node* b = next; b != NULL; b = b->next)
    {
      checkObjectCollision ( enemy, b->data, ENEMY_WIDTH, ENEMY_WIDTH, ENEMY_HEIGHT, ENEMY_HEIGHT );
    }
  
    if(enemy != NULL) // Make sure enemy was not deleted
    {
      moveObject( enemy, rand() % 3 - 1, 1 ); // Move enemy

      // Check if enemy exceeds bounds
      if(exceedsBounds(enemy))
      {
        deleteObject( &enemy );
        enemyList = deleteNode( enemyList, &current );
      }

      // Draw enemy
      if(enemy != NULL)
        drawObject( enemy );
    }

    // Next node
    current = next;
  }

    // Spawn an enemy every 3 seconds
    if( get_frame_counter() % 180 == 0 )
    {
      spawnEnemy( enemyList, rand() % 630, 0 );
    }

    return enemyList;
}

void updatePlayer( Object* player )
{
  // Obtain directional information (per axis) from selected gamepad
  gamepad_direction ( &player-> xdir, &player-> ydir );

  // Move the player
  moveObject( player, player->xdir, player->ydir );

  //Check the player bounds - this can go in a function later
  if (player -> x <  0) // left side
  {
      player -> x  = 1;
  }

  if (player -> x >  640) // right side
  {
      player -> x  = 639;
  }

  if (player -> y <  0) // top of screen
  {
      player -> y  = 1;
  }

  if (player -> y >  360) // bottom of screen
  {
      player -> y  = 359;
  }
  
  drawObject( player );
}


void main (void)
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
    Object* player  = createObject( PLAYER_TEXTURE, PLAYER_REGION, xPos, yPos, isActive, NULL );

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
      Object* enemy = createObject( ENEMY_TEXTURE, ENEMY_REGION, xPos, yPos, isActive, NULL );

      addBack(enemyList, enemy);
    }

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
        clear_screen (get_color_red (0));
        
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Draw the background
        //
        select_texture ( BACKGROUND_TEXTURE );
        select_region ( BACKGROUND_REGION );
        draw_region_at ( 0, 0 );

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Update the player
        //
        updatePlayer( player );
     
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Update the enemies 
        //
        enemyList = updateEnemies( enemyList );

        // End frame
        end_frame();
    }

    // Free our list and all its contents
    deleteList( &enemyList );
}
