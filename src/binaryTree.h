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
binaryTree * inOrder( binaryTree * myTree, Object * root) 
{
	Object * tmp;
	tmp 			= (Object *)malloc(sizeof(Object));
	tmp = root;
	if ( tmp == NULL)
	{
		return;
	}
	myTree = inOrder (myTree , tmp->prev);
	myTree = inOrder (myTree, tmp->next);
	free(tmp2);
return (myTree);
}
//preorder left, parent, right.
void preOrder( binaryTree * myTree, Object * root)
{
	Object * tmp;
	tmp				= (Object *)malloc(sizeof(Object));
	tmp = root;
	if (tmp != NULL)
	{
		preOrder ( myTree, tmp -> prev);
	}
	if (tmp == NULL)
	{
		return;
	}	
	if ( tmp != NULL)
	{
		preOrder ( myTree, tmp -> next);	
	}
	free(tmp);
}
//postorder right, parent, left.
void postOrder ( binaryTree * myTree, Object * root)
{
	Object * tmp;
	tmp				= (Object *)malloc(sizeof(Object));
	tmp = root;
	if ( tmp != NULL)
	{
		postOrder (myTree, tmp -> next);
	}
	if ( tmp == NULL)
	{
		return;
	}
	if ( tmp != NULL)
	{
		postOrder (myTree, tmp -> prev);
	}
	free(tmp);
}

binaryTree * obtainBinaryNode ( binaryTree * myTree, int pointsValue, Object * root, Object **thatNode);
	{
		Object * tmp;
		Object * tmp2;
		Object * tmp 	=	(Object *)malloc(sizeof(Object));
		Object * tmp2	=	(Object *)malloc(sizeof(Object));
		tmp2			= tmp;
		tmp				= root;
		if (tmp == NULL)
		{
			return (myTree)
		}
		if ( pointsValue > tmp -> value)
		{
			myTree = obtainBinaryNode (myTree, pointsValue, tmp -> next, **thatNode);
		}
		if ( pointsValue < tmp -> value)
		{
			myTree = obtainBinaryNode (myTree, pointsValue, tmp -> prev, **thatNode);
		}
// Cases where we could have the value!
		if ( pointsValue == tmp -> value)	
			{
				
		
		








#endif //BINARYTREE_H_

