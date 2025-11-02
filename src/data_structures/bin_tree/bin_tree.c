#ifndef BIN_TREE_C
#define BIN_TREE_C
#include "bin_node.c"
#include "../doubly_linked_list/doubly_linked_list.h"

struct BinTree
{
    BinNode* root;
};

//Compare A to B
bool BinTreeCompareKeys(int* a, int* b)
{
    if(a == NULL)
        return false;

    if(b == NULL)
        return false;

    return *a <= *b;
}

BinTree* ConstructBinTree()
{
    BinTree* tree = (BinTree*)malloc(sizeof(BinTree));
    tree->root  = NULL;
    return tree;
}

BinNode* searchTreeKey(BinTree* tree, int* value)
{
    BinNode* bestNode = tree -> root;

    while(bestNode != NULL)
    {
        if(BinTreeCompareKeys(value, bestNode -> key))
        {
            if(bestNode -> base.prev != NULL)
            {
                bestNode = (BinNode*)bestNode -> base.prev;
            }
            else
            {
                return bestNode;
            }
        }
        else
        {
            if(bestNode -> base.next != NULL)
            {
                bestNode = (BinNode*)bestNode -> base.next;
            }
            else
            {
                return bestNode;
            }
        }
    }
    return NULL;
}

void AddBinTree(BinTree* tree, BinNode* node)
{
    BinNode* parent = searchTreeKey(tree, node -> key);

    if(parent != NULL)
    {
        if(BinTreeCompareKeys(node -> key, parent -> key))
        {
            parent -> base.prev = &node -> base;
        }
        else
        {
            parent -> base.next = &node -> base;
        }
    }
    else
    {
        tree -> root = node;
    }
}

enum ParentType
{
    lesser,
    greater,
    none
};

void extractNode(BinNode* parent, BinNode* node, ParentType type)
{
    BinNode* maxNode;
    BinNode** maxLink;

    if(node -> base.prev == NULL)
    {
        if(type == lesser)
            parent -> base.next = node -> base.next;
        else if(type == greater)
            parent -> base.prev = node -> base.next;

        node -> base.next = NULL;
        node -> base.prev = NULL;
        return;
    }

    if(node -> base.next == NULL)
    {
        if(type == lesser)
            parent -> base.next = node -> base.prev;
        else if(type == greater)
            parent -> base.prev = node -> base.prev;

        node -> base.next = NULL;
        node -> base.prev = NULL;
        return;
    }


    maxLink = (BinNode**)&node -> base.prev;
    maxNode = (BinNode*)node -> base.prev;

    while(maxNode -> base.next != NULL)
    {
        maxLink = (BinNode**)&maxNode -> base.next;
        maxNode = (BinNode*)maxNode -> base.next;
    }

    *maxLink = (BinNode*)maxNode -> base.prev;

    maxNode -> base.next = node -> base.next;
    maxNode -> base.prev = node -> base.prev;

    if(type == lesser)
        parent -> base.next = &maxNode -> base;
    else if(type == greater)
        parent -> base.prev = &maxNode -> base;

}

void grabRecursive(BinNode* position, BinNode* goal)
{
    //Find direction of goal
    if(BinTreeCompareKeys(goal -> key, position -> key))
    {
        //Goal is immediate
        if(position -> base.prev == &goal -> base)
        {
            extractNode(position, goal, greater);
        }
        else
        {
           grabRecursive((BinNode*)position -> base.prev, goal);
        }
    }
    else
    {
        //Goal is immediate
        if((BinNode*)position -> base.next == goal)
        {
            extractNode(position, goal, lesser);
        }
        else
        {
            grabRecursive((BinNode*)position -> base.next, goal);
        }
    }
}

void grab(BinTree* tree, BinNode* node)
{
    if(node == NULL || tree == NULL)
        return;

    if(tree -> root == node)
    {
        extractNode(node, node, none);
    }

    grabRecursive(tree -> root, node);
}

void PreOrder(BinNode* node, List* list)
{
    if(node != NULL)
    {
        if(node -> base.prev != NULL)
            PreOrder((BinNode*)node -> base.prev, list);

        append(list, list -> tail, createNode(node -> base.data));

        if(node -> base.next != NULL)
            PreOrder((BinNode*)node -> base.next, list);
    }
}

BinNode* grabRandom(BinTree* tree)
{
    if(tree != NULL)
    {
        if(tree -> root != NULL)
        {
            BinNode** endLink     = &tree -> root;
            BinNode*  currentNode = tree -> root;

            while(true)
            {
                if(currentNode -> base.next != NULL &&
                   currentNode -> base.prev != NULL)
                {
                    if(rand() % 2 == 1)
                    {
                        endLink     = (BinNode**)&currentNode -> base.next;
                        currentNode = (BinNode*)  currentNode -> base.next;
                    }
                    else
                    {
                        endLink     = (BinNode**)&currentNode -> base.prev;
                        currentNode = (BinNode*)  currentNode -> base.prev;
                    }
                }
                else if(currentNode -> base.next != NULL)
                {
                    endLink     = (BinNode**)&currentNode -> base.next;
                    currentNode = (BinNode*)  currentNode -> base.next;
                }
                else if(currentNode -> base.prev != NULL)
                {
                    endLink     = (BinNode**)&currentNode -> base.prev;
                    currentNode = (BinNode*)  currentNode -> base.prev;
                }
                else
                {
                    break;
                }
            }

        *endLink = NULL;
        return currentNode;
        }
    }
    return NULL;
}

#endif // BIN_TREE_C