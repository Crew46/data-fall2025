#ifndef GAME_OBJECT_DECLARATION_H
#define GAME_OBJECT_DECLARATION_H

struct GameObject
{
    Object base; //base object
    DoublyLinkedList* components; //list of components
    DoublyLinkedList* children; //list of child game objects
    int gameObjectID;
};

#endif // GAME_OBJECT_DECLARATION_H