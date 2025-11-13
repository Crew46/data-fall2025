#ifndef BIN_TREE_C
#define BIN_TREE_C
#include "bin_node.c"
#include "../doubly_linked_list/doubly_linked_list.h"

struct BinTree
{
    BinNode* root;
};

//Compare A to B
bool BinTreeCompareKeys(int a, int b)
{
    return a <= b;
}

BinTree* ConstructBinTree()
{
    BinTree* tree = (BinTree*)malloc(sizeof(BinTree));
    tree->root  = NULL;
    return tree;
}

BinNode* searchTreeKey(BinTree* tree, int value)
{
    BinNode* bestNode = tree -> root;
    if(tree -> root == NULL)
    {
        return NULL;
    }

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
    if(tree -> root == NULL)
    {
        tree -> root = node;
        node -> base.next = NULL;
        node -> base.prev = NULL;
        return;
    }

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

void extractNode(BinNode* node, Node** nodeLink)
{
    BinNode* replacement     = (BinNode*)node -> base.prev;
    Node**   replacementLink = &node -> base.prev;

    if(node == NULL || nodeLink == NULL)
        return;

    if(replacement == NULL)
    {
        *nodeLink = node -> base.next;

        node -> base.next = NULL;
        node -> base.prev = NULL;
        return;
    }

    while(replacement -> base.next != NULL)
    {
        replacementLink = &replacement -> base.next;
        replacement     = (BinNode*)replacement -> base.next;
    }

    *replacementLink = replacement -> base.prev;

    replacement -> base.next = node -> base.next;
    replacement -> base.prev = node -> base.prev;

    *nodeLink = (Node*)replacement;
}

void grabRecursive(BinNode* position, BinNode* goal)
{
    //Find direction of goal
    if(BinTreeCompareKeys(goal -> key, position -> key))
    {
        //Goal is immediate
        if(position -> base.prev == &goal -> base)
        {
            extractNode(goal, &position -> base.prev);
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
            extractNode(goal, &position -> base.next);
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
        extractNode(node, (Node**)&tree -> root);
        return;
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

void PostOrder(BinNode* node, List* list)
{
    if(node != NULL)
    {
        if(node -> base.next != NULL)
            PostOrder((BinNode*)node -> base.next, list);

        append(list, list -> tail, createNode(node -> base.data));

        if(node -> base.prev != NULL)
            PostOrder((BinNode*)node -> base.prev, list);
    }
}

void InOrder(BinNode* node, List* list)
{
    if(node != NULL)
    {
        append(list, list -> tail, createNode(node -> base.data));

        if(node -> base.prev != NULL)
            InOrder((BinNode*)node -> base.prev, list);

        if(node -> base.next != NULL)
            InOrder((BinNode*)node -> base.next, list);

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

BinNode* findDeepest(BinNode* node, int* depth)
{
    BinNode* deepestLess  = NULL;
    int      prevDepth    = *depth + 1;
    BinNode* deepestMore  = NULL;
    int      nextDepth    = *depth + 1;

    //NULL check
    if(node == NULL)
        return NULL;

    //Has no children, thus deepest
    if(node -> base.prev == NULL && node -> base.next == NULL)
        return node;

    //Has no prev children, thus deepest is in next
    if(node -> base.prev == NULL)
    {
        *depth += 1;
        return findDeepest((BinNode*)node -> base.next, depth);
    }

    //Has no next children, thus deepest is in prev
    if(node -> base.next == NULL)
    {
        *depth += 1;
        return findDeepest((BinNode*)node -> base.prev, depth);
    }

    deepestLess = findDeepest((BinNode*)node -> base.prev, &prevDepth);
    deepestMore = findDeepest((BinNode*)node -> base.next, &nextDepth);

    if(prevDepth > nextDepth)
    {
        *depth = prevDepth;
        return deepestLess;
    }
    else
    {
        *depth = nextDepth;
        return deepestMore;
    }
}

#endif // BIN_TREE_C