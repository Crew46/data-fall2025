#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "binary_node.h"

struct BinaryTree
{
  BinaryNode* root;
};

BinaryTree* mkBinTree()
{
  BinaryTree* bTree = (BinaryTree*)malloc(sizeof(BinaryTree));
  bTree->root = mkBinNode(0);
  return bTree;
}
#endif
