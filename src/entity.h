#ifndef ENTITY_H // entity.h
#define ENTITY_H

struct Object;

// Entity struct which is a substruct of Object
struct Entity
{
  Object obj;
  Weapon* weapon;
};

Entity* createEntity(int textureID, int regionID, int x, int y, int status, WeaponType wType)
{
  Entity* entity = (Entity*)malloc(sizeof(Entity));
  initObject(&entity->obj, Object_Type_Entity, textureID, regionID, x, y, status);
  entity->weapon  = createWeapon(wType);
  return entity;
}

DoublyLinkedList* spawnEnemy(DoublyLinkedList* list, int xPos, int yPos, int status, WeaponType wType)
{
  Entity* entity = createEntity( ENEMY_TEXTURE, ENEMY_REGION, xPos, yPos, status, wType);
  entity->obj.vx = 1;
  entity->obj.vy = 1;
  list = append( list, list->tail, &entity->obj );

  return list;
}

DoublyLinkedList* updateEnemies(DoublyLinkedList* enemyList)
{
  Node* current = enemyList->head;
  while (current != NULL)
  {
      Node* next  = current->next;    
      Object* enemy = current->data;

      if (enemy == NULL || (enemy->status & IS_ACTIVE_FLAG) == 0) {
          if (enemy) deleteObject(&enemy);
          enemyList = deleteNode(enemyList, &current);
          current = next;              
          continue;
      }

      // Move active enemy
      moveObject(enemy, rand() % 3 - 1, 1);  

      // If the enemy exceeds bounds, delete it
      if (exceedsBounds(enemy)) {
          deleteObject(&enemy);
          enemyList = deleteNode(enemyList, &current);
      }

      current = next;                  
  }

  if (get_frame_counter() % 180 == 0) {
      for (int i = 0; i < 3; i++) {
          enemyList = spawnEnemy(enemyList, rand() % 630, 0, IS_ACTIVE_FLAG, Weapon_Type_Laser);
      }
  }
  return enemyList;
}

DoublyLinkedList* updateAmmo(DoublyLinkedList* ammoList)
{
  if(!ammoList)
    return ammoList;

  Node* temp = ammoList->head;
  while(temp != NULL)
  {
    Node* curr = temp;
    temp = temp->next;                 

    Object* o = curr->data;           

    // If bullets are inactive, delete them
    if ((o->status & IS_ACTIVE_FLAG) == 0) {
        deleteObject(&curr->data);
        ammoList = deleteNode(ammoList, &curr);
        continue;
    }

    moveObject(o, o->dx, o->dy);

    if (exceedsBounds(o)) {
        deleteObject(&curr->data);
        ammoList = deleteNode(ammoList, &curr);
    }
  }
  
  return ammoList;
}


Entity* playerShoot(Entity* player)
{
  Laser* laser = createLaser(LASER_TEXTURE, LASER_REGION, player->obj.x + 12, player->obj.y, IS_ACTIVE_FLAG);
  Object* laserObj = &laser->obj;
  player->weapon->ammoList = append(player->weapon->ammoList, player->weapon->ammoList->head, laserObj );

  return player;
}

Entity* updatePlayer(Entity* player)
{
   if ( (player->obj.status & IS_ACTIVE_FLAG) == 0 ) // Player is inactive
        return player;

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
        // Deactivate both the enemy and the bullet
        enemy->data->status &= ~IS_ACTIVE_FLAG;
        ammo->data->status &= ~IS_ACTIVE_FLAG;

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
