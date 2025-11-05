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
		return (myTree);
	}
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
		if ( newNode -> points <= tmp -> points)
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
return (myTree);
}



//inorder: parent, left, right.




//preorder left, parent, right.


//postorder right, parent, left.









#endif //BINARYTREE_H_

