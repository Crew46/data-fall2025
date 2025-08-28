#include "input.h"
#include "misc.h"
#include "video.h"
#include "time.h"

#define  BACKGROUND_TEXTURE 0
#define  PLAYER_TEXTURE     1
#define  ENEMY_TEXTURE      -1

#define  BACKGROUND_REGION  0
#define  PLAYER_REGION      1
#define  ENEMY_REGION       86

#define  SCREEN_WIDTH       640
#define  SCREEN_HEIGHT      360


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

void deleteNode(DoublyLinkedList* list, Node** node)
{
  if(!list || !*node || !node)
    return;

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

void addFront(DoublyLinkedList* list, Object* data)
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

}

void addBack(DoublyLinkedList* list, Object* data)
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

void updateEnemies(DoublyLinkedList* enemyList)
{
  Node* current = enemyList->head;
  Node* next = NULL;
  Object* enemy = NULL;
  while(current != NULL)
  {
    next = current->next;

    // Move enemy 
    enemy = current->data;
    enemy  -> xdir   = rand() % 3 - 1;
    enemy  -> ydir   = 1; //rand () % 3 - 1;
    enemy  -> x      = enemy  -> x + enemy  -> xdir;
    enemy  -> y      = enemy  -> y + enemy  -> ydir;
    

    if(exceedsBounds(enemy))
    {
      deleteObject(&enemy);
      deleteNode(enemyList, &current);
    }

    // Draw enemy
    if(enemy != NULL)
    {
      select_texture (enemy->textureID);
      select_region  (enemy->regionID);
      draw_region_at (enemy->x, enemy->y);
    }
    // Next node
    current = next;
  }
}


void main (void)
{
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Seed the rng
    //
    srand(get_time());

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Create our player instance
    //
    Object *player       = (Object *) malloc (sizeof (Object) * 1); 
    player -> next       = NULL;
    player -> x          = 360;
    player -> y          = 300;
    player -> textureID  = PLAYER_TEXTURE;
    player -> regionID   = PLAYER_REGION;

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Create an enemy instance
    //
    //Object *enemy        = (Object *) malloc (sizeof (Object) * 1); 
    //enemy  -> next       = NULL;
    //enemy  -> x          = rand () % 630;
    //enemy  -> y          = 0;
    //enemy  -> textureID  = ENEMY_TEXTURE;
    //enemy  -> regionID   = ENEMY_REGION;


    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Create enemy list
    //
    DoublyLinkedList* enemyList = createList(); 
    for(int i = 0; i < 5; ++i) // Add 5 enemies to start 
    {
      int xPos = rand() % 630;
      int yPos = 0;
      bool isActive = true;
      Object* enemy = createObject(ENEMY_TEXTURE, ENEMY_REGION, xPos, yPos, isActive, NULL);

      addBack(enemyList, enemy);
    }

    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Define the background texture and region
    //
    select_texture (BACKGROUND_TEXTURE);
    select_region (BACKGROUND_REGION);
    define_region_topleft (0, 0, 639, 359);
    
    ////////////////////////////////////////////////////////////////////////////////////
    //
    // Define the player texture and region
    //
    select_texture (PLAYER_TEXTURE);
    select_region (PLAYER_REGION);
    define_region (0, 0, 31, 31, 0, 0);
    
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
        select_texture (BACKGROUND_TEXTURE);
        select_region (BACKGROUND_REGION);
        draw_region_at (0, 0);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Obtain directional information (per axis) from selected gamepad
        //
        gamepad_direction (&player -> xdir, &player -> ydir);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Adjust player position based on recently obtained gamepad information
        //
        player -> x      = player -> x + player -> xdir;
        player -> y      = player -> y + player -> ydir;

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Player/playfield bounds checking
        //
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
        
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Select texture and region for the player, and draw it
        //
        select_texture (player -> textureID);
        select_region  (player -> regionID);
        draw_region_at (player -> x, player -> y);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Update the enemies 
        //
        updateEnemies(enemyList);

        ////////////////////////////////////////////////////////////////////////////////
        //
        // Adjust enemy position based on randomness
        //
        //enemy  -> xdir   = rand () % 3 - 1;
        //enemy  -> ydir   = 1; //rand () % 3 - 1;
        //enemy  -> x      = enemy  -> x + enemy  -> xdir;
        //enemy  -> y      = enemy  -> y + enemy  -> ydir;

        
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Enemy/playfield bounds checking
        //

 
        ////////////////////////////////////////////////////////////////////////////////
        //
        // Select texture and region for the enemy, and draw it
        //
        //select_texture (enemy  -> textureID);
        //select_region  (enemy  -> regionID);
        //draw_region_at (enemy  -> x, enemy  -> y);

        end_frame ();
    }
    deleteList(&enemyList);
}
