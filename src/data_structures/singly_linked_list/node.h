#ifndef NODE_H
#define NODE_H
#include "../../architecture/object/object.h"

struct Node 
{
    Object* data;
    Node* next;
};

#endif //NODE_H