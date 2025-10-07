#ifndef ENTITY_H // entity.h
#define ENTITY_H

struct Object;
// Entity struct which is a substruct of Object
struct Entity
{
  Object obj;
  Weapon* weapon;
};

Entity* createEntity(int textureID, int regionID, int x, int y, bool isActive, WeaponType wType)
{
  Entity* entity = (Entity*)malloc(sizeof(Entity));
  initObject(&entity->obj, Object_Type_Entity, textureID, regionID, x, y, isActive);
  entity->weapon  = createWeapon(wType);
  return entity;
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
      if(enemy && checkObjectCollision(enemy->data, ammo->data, 
            ENEMY_WIDTH, LASER_WIDTH, ENEMY_HEIGHT, LASER_HEIGHT))
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

#endif
