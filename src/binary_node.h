#ifndef BINARY_NODE_H
#define BINARY_NODE_H

#include "../node.h"

struct BinaryNode
{
  Node node;
  int data;
};

BinaryNode* mkBinNode(int data)
{
  BinaryNode* bNode = (BinaryNode)malloc(sizeof(BinaryNode));
  bNode->node = createNode();
  bNode->data = data.
}

void DeconstructBinaryNode(BinaryNode* bNode)
{
    free(bNode);
}

#endif
