#ifndef BIN_NODE_C
#define BIN_NODE_C
#include "../../object.h"
#include "../doubly_linked_list/doubly_linked_list.h"

struct BinNode
{
    Node base;
    int* key;
};

BinNode* ConstructBinNode(Object* data)
{
    BinNode* node   = (BinNode*)malloc(sizeof(BinNode));
    node->base.next = NULL;
    node->base.prev = NULL;
    node->base.data = data;
    node->key       = &data -> x;
    return node;
}

void DeconstructBinNode(BinNode* BinNode)
{
    free(BinNode);
}


#endif //BIN_NODE_C