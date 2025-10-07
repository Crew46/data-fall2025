#include "input.h"
#include "misc.h"
#include "video.h"
#include "time.h"

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

// We need to know if the object is embedded so we can free memory properly
enum ObjectType
{
  Object_Type_None,
  Object_Type_Laser,
  Object_Type_Weapon,
  Object_Type_Entity
};
// Object struct which will be our base struct 
struct Object
{
  ObjectType  type;
  int         textureID;
  int         regionID;
  int         id;
  int         x;
  int         y;
  int         dx;
  int         dy;
  int         vx;
  int         vy;
  bool        isActive;
};

// This function is mainly for our embedded object 
void initObject(Object* obj, ObjectType objT, int textureID, int regionID, int xPos, int yPos, bool isActive)
{
  obj->type       = objT;
  obj->textureID  = textureID;
  obj->regionID   = regionID;
  obj->x          = xPos;
  obj->y          = yPos;
  obj->vx         = 1; // Set to 1 for now, will make it customizable eventually
  obj->vy         = 1;
  obj->isActive   = isActive;
  
}

Object* createObject(int textureID, int regionID, int x, int y, bool isActive)
{
  Object* obj     = (Object*)malloc(sizeof(Object));
  obj->type       = Object_Type_None; // Has no parent
  obj->textureID  = textureID;
  obj->regionID   = regionID;
  obj->x          = x;
  obj->y          = y;
  obj->isActive   = isActive;
  
  return obj;
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

struct Stack
{
  Node* top;
  DoublyLinkedList* list;
};

Stack* createStack()
{
  Stack* stack = (Stack*)malloc(sizeof(Stack));
  stack->top = NULL;
  stack->list = createList();
}

Stack* push(Stack* stack, Object* newObj)
{
  stack->list = insert(stack->list, stack->list->head, newObj);
  stack->top = stack->list->head;
  return stack;
}

Node* pop(Stack** stack)
{
  Node* prevTop = obtain(&(*stack)->list, (*stack)->top);
  (*stack)->top = (*stack)->list->head;

  return prevTop;
}

struct Laser
{
  Object obj;
};

Laser* createLaser(int textureID, int regionID, int x, int y, bool isActive)
{
  Laser* laser = (Laser*)malloc(sizeof(Laser));
  initObject(&laser->obj, Object_Type_Laser, textureID, regionID, x, y, isActive);

  // Set these manually for now
  laser->obj.dx = 0;
  laser->obj.vx = 1;
  laser->obj.dy = -1;
  laser->obj.vy = 5;
  return laser;
}
enum WeaponType
{
  Weapon_Type_None,
  Weapon_Type_Laser,
};

struct Weapon
{
  WeaponType weaponType;
  DoublyLinkedList* ammoList;
};

Weapon* createWeapon(WeaponType wType)
{
  Weapon* weapon = (Weapon*)malloc(sizeof(Weapon));
  weapon->weaponType = wType;
  weapon->ammoList = createList();
  return weapon;
}

// Entity struct which is a substruct of Object
struct Entity
{
  Object obj;
  Weapon* weapon;
};

void deleteObject(Object** obj)
{
  
  switch((*obj)->type)
  {
    case Object_Type_None: {
      free(*obj);
      break;
    }
    case Object_Type_Laser: {
      Laser* laser = (Laser*)*obj;
      free(laser);
      break;
    }
    case Object_Type_Weapon: {
      Weapon* weapon = (Weapon*)*obj;
      free(weapon);
      break;
    }
    case Object_Type_Entity: {
      Entity* entity = (Entity*)*obj;
      free(entity);
      break;
    }
    default:
      break;
  }
  *obj = NULL;
}

Entity* createEntity(int textureID, int regionID, int x, int y, bool isActive, WeaponType wType)
{
  Entity* entity = (Entity*)malloc(sizeof(Entity));
  initObject(&entity->obj, Object_Type_Entity, textureID, regionID, x, y, isActive);
  entity->weapon  = createWeapon(wType);
  return entity;
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

void moveObject(Object* obj, int dx, int dy)
{
  obj  -> dx    = dx;
  obj  -> dy    = dy;
  obj  -> x     = obj  -> x + obj  -> dx * obj->vx;
  obj  -> y     = obj  -> y + obj  -> dy * obj->vy;
}
void drawObject(Object* obj)
{
  select_texture ( obj->textureID );
  select_region  ( obj->regionID );
  draw_region_at ( obj->x, obj->y );
}
bool checkObjectCollision(Object* objA, Object* objB, int objA_Width, int objB_Width, int objA_Height, int objB_Height)
{
  // Check if objects are NULL
  if(!objA || !objB)
    return false;

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

    return true;
  }

  return false;
}

DoublyLinkedList* spawnEnemy(DoublyLinkedList* list, int xPos, int yPos, WeaponType wType)
{
  Entity* entity = createEntity( ENEMY_TEXTURE, ENEMY_REGION, xPos, yPos, true, wType);
  entity->obj.vx = 1;
  entity->obj.vy = 1;
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

    }

    // Next node
    current = next;
  }

    // Spawn 3 enemies every 3 seconds
    if( get_frame_counter() % 180 == 0 )
    {
      for(int i = 0; i < 3; i++)
      {
        enemyList = spawnEnemy( enemyList, rand() % 630, 0, Weapon_Type_Laser );
      }
    }

    return enemyList;
}

DoublyLinkedList* updateAmmo(DoublyLinkedList* ammoList)
{
  if(!ammoList)
    return ammoList;

  Node* temp = ammoList->head;
  Node* next = NULL;
  while(temp != NULL)
  {
    next = temp->next;
    moveObject(temp->data, temp->data->dx, temp->data->dy);

    if(exceedsBounds(temp->data))
    {
      deleteObject(&temp->data);
      ammoList = deleteNode(ammoList, &temp);
    }
    
    temp = next;
  }

  return ammoList;
}

Entity* playerShoot(Entity* player)
{
  Laser* laser = createLaser(LASER_TEXTURE, LASER_REGION, player->obj.x + 12, player->obj.y, true);
  Object* laserObj = &laser->obj;
  player->weapon->ammoList = append(player->weapon->ammoList, player->weapon->ammoList->head, laserObj );
  
  return player;
} 

Entity* updatePlayer(Entity* player)
{
  Object* playerObj = &player->obj;
  gamepad_direction(&playerObj->dx, &playerObj->dy);
  moveObject(playerObj, playerObj->dx, playerObj->dy);


  if (playerObj->x < 0)   playerObj->x = 1;
  if (playerObj->x > 640) playerObj->x = 639;
  if (playerObj->y < 0)   playerObj->y = 1;
  if (playerObj->y > 360) playerObj->y = 359;

  if(gamepad_button_a() == 1)
  {
    player = playerShoot(player);
  }
  return player;
}

void checkAmmoCollisionWithEnemies(DoublyLinkedList** ammoList, DoublyLinkedList** enemyList)
{
  Node* ammo = (*ammoList)->head;
  Node* enemy = NULL;
  while(ammo != NULL)
  {
    Node* ammoNext = ammo->next;
    enemy = (*enemyList)->head;
    while(enemy != NULL)
    {
      Node* enemyNext = enemy->next;
      if(enemy && checkObjectCollision(enemy->data, ammo->data, ENEMY_WIDTH, LASER_WIDTH, ENEMY_HEIGHT, LASER_HEIGHT)) 
      {
        // Delete both the enemy and the bullet
        deleteObject(&enemy->data);
        deleteNode(*enemyList, &enemy);

        deleteObject(&ammo->data);
        deleteNode(*ammoList, &ammo);

        break;
      }
      enemy = enemyNext;
    }

    ammo = ammoNext;
  }
}

void renderPlayer(Entity* player)
{
  Object* playerObj = &player->obj;
  drawObject(playerObj);
}
void renderEnemies(DoublyLinkedList* enemyList)
{
  Node* temp = enemyList->head;
  while(temp != NULL)
  {
    drawObject(temp->data);
    temp = temp->next;
  }
}
void renderAmmo(DoublyLinkedList* ammoList)
{
  Node* temp = ammoList->head;
  while(temp != NULL)
  {
    drawObject(temp->data);
    temp = temp->next;
  }
}

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
  player->obj.vx = 3; // Set manually for now
  player->obj.vy = 1;

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
    // Define the laser texture and region
    //
    select_texture( LASER_TEXTURE );
    select_region( LASER_REGION );
    define_region_topleft( 0, 0, 3, 10 );

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
