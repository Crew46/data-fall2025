#ifndef BINARYTREE_H_
#define BINARYTREE_H_

binaryTree * mkBinaryTree ()
{
	binaryTree * myTree 	= (binaryTree *)malloc(sizeof(binaryTree));
	if (myTree == NULL)
	{
		exit ();
	}
	myTree -> root = NULL;
return (myTree);
}
// This will add to a binary tree. 
// next = right and prev = left;
binaryTree * addBinaryNode (binaryTree * myTree, Object * newNode)
{
	if ( myTree -> root == NULL)
	{
		myTree -> root 	= newNode;
	}
	else
	{
		Object * tmp		= NULL;
		tmp					= myTree -> root;
		while (1)
		{
// If the newNode is greater than the root we will go right.
			if ( newNode -> points > tmp->points)
			{
				if ( tmp -> next == NULL)
				{
					tmp -> next = newNode;
					break;
				}
				else 
				{
					tmp 		= tmp -> next;
				}
			}
// Otherwise we will go left if lesser than or equal.
			else
			{
				if ( tmp -> prev == NULL)
				{
					tmp -> prev = newNode;
					break;
				}
				else
				{
					tmp = tmp -> prev;
				}
			}
		}
	}
return (myTree);
}



//inorder: parent, left, right.
void inOrder( binaryTree * myTree, Object * root) 
{
	Object * tmp;
	tmp = root;
	if ( tmp == NULL)
	{
		return;
	}
	inOrder (myTree, tmp->prev);
	tmp = root;
	inOrder (myTree, tmp->next);
	tmp = root;
}
//preorder left, parent, right.
void preOrder( binaryTree * myTree, Object * root)
{
	Object * tmp;
	tmp = root;
	if (tmp != NULL)
	{
		preOrder ( myTree, tmp -> prev);
	}
	tmp = root;
	if (tmp == NULL)
	{
		return;
	}	
	tmp = root;
	if ( tmp != NULL)
	{
		preOrder ( myTree, tmp -> next);	
	}
	tmp = root;
}
//postorder right, parent, left.










#endif //BINARYTREE_H_

