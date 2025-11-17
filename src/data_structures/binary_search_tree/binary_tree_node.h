#ifndef BINARY_TREE_NODE_H
#define BINARY_TREE_NODE_H
#include "../../architecture/object/object.h"

struct BinaryTreeNode
{
    BinaryTreeNode* left; 
    BinaryTreeNode* right; 
    Object* data;
    int key;
};

#endif //BINARY_TREE_NODE_H