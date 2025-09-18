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

// Object struct which will be our base struct 
struct Object
{
  int     textureID;
  int     regionID;
  int     id;
  int     x;
  int     y;
  int     xDir;
  int     yDir;
  bool    isActive;
};

void initObject(Object* obj, int textureID, int regionID, int xPos, int yPos, bool isActive)
{
  obj->textureID  = textureID;
  obj->regionID   = regionID;
  obj->x          = xPos;
  obj->y          = yPos;
  obj->isActive   = isActive;
  
}

Object* createObject(int textureID, int regionID, int x, int y, bool isActive)
{
  Object* obj     = (Object*)malloc(sizeof(Object));
  obj->textureID  = textureID;
  obj->regionID   = regionID;
  obj->x          = x;
  obj->y          = y;
  obj->isActive   = isActive;
  
  return obj;
}


enum WeaponType
{
  Weapon_Type_None,
  Weapon_Type_Laser,
};

struct Weapon
{
  WeaponType weaponType;
};

Weapon* createWeapon(WeaponType wType)
{
  Weapon* weapon = (Weapon*)malloc(sizeof(Weapon));
  weapon->weaponType = wType;
  return weapon;
}

// Entity struct which is a substruct of Object
struct Entity
{
  Object obj;
  Weapon* weapon;
};

Object* deleteObject(Object** obj)
{
  Entity* parent = (Entity*)*obj;
  free(parent);
  *obj = NULL;
}
Entity* createEntity(int textureID, int regionID, int x, int y, bool isActive, WeaponType wType)
{
  Entity* entity = (Entity*)malloc(sizeof(Entity));
  initObject(&entity->obj, textureID, regionID, x, y, isActive);
  entity->weapon  = createWeapon(wType);
  return entity;
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
//  Doubly Linked List struct and helpers
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

// Insert a new object
DoublyLinkedList* insert(DoublyLinkedList* list, Node* targetNode, Object* newObj)
{
  if(!list || !newObj)
    return list;

  Node* newNode = createNode(newObj);

  // List is empty
  if( !list->head && !list->tail )
  {
    list->head = newNode;
    list->tail = newNode;
  }
  else if(list->head == targetNode)
  {
    list->head = newNode;
    newNode->next = targetNode;
    targetNode->prev = newNode;
  }
  else
  {
    newNode->prev = targetNode->prev;
    targetNode->prev->next = newNode;
    targetNode->prev = newNode;
    newNode->next = targetNode;
  }

  return list;
}

// Append a new object
DoublyLinkedList* append(DoublyLinkedList* list, Node* targetNode, Object* newObj)
{
  if(!list || !newObj)
    return list;

  Node* newNode = createNode(newObj);

  // List is empty
  if( !list->head && !list->tail )
  {
    list->head = newNode;
    list->tail = newNode;
  }
  else if(list->tail == targetNode)
  {
    list->tail = newNode;
    newNode->prev = targetNode;
    targetNode->next = newNode;
  }
  else
  {
    newNode->next = targetNode->next;
    targetNode->next->prev = newNode;
    targetNode->next = newNode;
    newNode->prev = targetNode;
  }

  return list;
}

Node* obtain(DoublyLinkedList** list, Node* node)
{
  if(!list || !(*list) || !node)
    return NULL;

  // Only one node in the list
  if(node == (*list)->head && node == (*list)->tail)
  {
    (*list)->head = NULL;
    (*list)->tail = NULL;
  }
  else if(node == (*list)->head)
  {
    (*list)->head = node->next;
    node->next->prev = NULL;
    node->next = NULL;
  }
  else if(node == (*list)->tail)
  {
    (*list)->tail = node->prev;
    node->prev->next = NULL;
    node->prev = NULL;
  }
  else
  {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->next = NULL;
    node->prev = NULL;
  }

  return node;
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

void moveObject(Object* obj, int xDir, int yDir)
{
  obj  -> xDir   = xDir;
  obj  -> yDir   = yDir;
  obj  -> x      = obj  -> x + obj  -> xDir;
  obj  -> y      = obj  -> y + obj  -> yDir;
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

DoublyLinkedList* spawnEnemy(DoublyLinkedList* list, int xPos, int yPos, WeaponType wType)
{
  Entity* entity = createEntity( ENEMY_TEXTURE, ENEMY_REGION, xPos, yPos, true, wType);
  list = append( list, list->tail, &entity->obj );

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
      enemyList = spawnEnemy( enemyList, rand() % 630, 0, Weapon_Type_Laser );
    }

    return enemyList;
}

Entity* updatePlayer(Entity* player)
{
  Object* playerObj = &player->obj;
  gamepad_direction(&playerObj->xDir, &playerObj->yDir);
  moveObject(playerObj, playerObj->xDir, playerObj->yDir);

  if (playerObj->x < 0)   playerObj->x = 1;
  if (playerObj->x > 640) playerObj->x = 639;
  if (playerObj->y < 0)   playerObj->y = 1;
  if (playerObj->y > 360) playerObj->y = 359;

  drawObject(playerObj);
  return player;
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
  Entity* player = createEntity( PLAYER_TEXTURE, PLAYER_REGION, xPos, yPos, isActive, Weapon_Type_Laser );

  ////////////////////////////////////////////////////////////////////////////////////
  //
  //
  // Create enemy list
    
  DoublyLinkedList* enemyList = createList();
  for(int i = 0; i < 5; ++i) // Add 5 enemies to start
  {
    int  xPos     = rand() % 630;
    int  yPos     = 0;
    bool isActive = true;
    Entity* enemy = createEntity( ENEMY_TEXTURE, ENEMY_REGION, xPos, yPos, isActive, Weapon_Type_Laser );

    enemyList = append(enemyList, enemyList->tail, &enemy->obj);
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
