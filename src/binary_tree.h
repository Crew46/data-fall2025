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
  bTree->root = NULL;
  return bTree;
}

void binTreeInsert(BinaryTree* tree, BinaryNode* node)
{
  if (tree == NULL || node == NULL)
      return;

  node->node.prev = NULL;   // left child
  node->node.next = NULL;   // right child

  // Check if tree has root
  if (tree->root == NULL)
  {
      tree->root = node;
      return;
  }

  BinaryNode* current = tree->root;

  while (true)
  {
    if (node->data <= current->data)
    {
      // Go Left
      if (current->node.prev == NULL)
      {
          // Spot found down the left subtree
          current->node.prev = (Node*)&node->node;
          break;
      }
      else
      {
          // keep going down the left subtree
          current = (BinaryNode*)current->node.prev;
      }
    }
    else
    {
      // Go right
      if (current->node.next == NULL)
      {
          // Spot found on the right subtree
          current->node.next = (Node*)&node->node;
          break;
      }
      else
      {
          // keep going down the right subtree
          current = (BinaryNode*)current->node.next;
      }
    }
  }
}
