#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
#include "../doubly_node.h"

struct BinarySearchTree
{
    DoublyNode* root;
};

void InOrder(BinarySearchTree* tree, DoublyNode* node);
void PreOrder(BinarySearchTree* tree, DoublyNode* node);
void PostOrder(BinarySearchTree* tree, DoublyNode* node);

#endif //BINARY_SEARCH_TREE_H