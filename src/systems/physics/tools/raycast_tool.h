#ifndef RAYCAST_TOOL_H
#define RAYCAST_TOOL_H
#include "../collider/collider.h" 
#include "../../../vector/vector2.h"
#include "../../../data_structures/doubly_linked_list/doubly_node.h"

//return a list of colliders that ray passed through; of no particular order 
DoublyLinkedList* CastRay(Vector2* vector, Vector2* origin);

#endif //RAYCAST_TOOL_H