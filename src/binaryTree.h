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
bool inOrder( binaryTree * myTree, Object * root, int pointsValue) 
{
	Object * tmp	= NULL;
	tmp				= root;
	if ( tmp == NULL)
	{
		return (false);
	}
	if ( tmp-> points == pointsValue)
	{
		return (true);
	}
	
	if (inOrder (myTree , tmp->prev, pointsValue) == true)
	{
		return (true);
	}
	if (inOrder (myTree, tmp->next, pointsValue) == true)
	{
		return (true);
	}
return (false);
}
//preorder left, parent, right.
bool preOrder( binaryTree * myTree, Object * root)
{
	Object * tmp	= NULL;
	tmp = root;
	if (tmp != NULL)
	{
		if ( preOrder ( myTree, tmp -> prev) == true);
		{
			return (true);
		}
	}
	if (tmp == NULL)
	{
		return false;
	}	
	if ( tmp != NULL)
	{
		if ( preOrder ( myTree, tmp -> next) == true);
		{
			return (true);
		}	
	}
	return false;
}
//postorder right, parent, left.
bool postOrder ( binaryTree * myTree, Object * root)
{
	Object * tmp = NULL;
	tmp = root;
	if ( tmp != NULL)
	{
		if ( postOrder (myTree, tmp -> next) == true)
		{
			return (true);
	}
	if ( tmp == NULL)
	{
		return (false);
	}
	if ( tmp != NULL)
	{
		if ( postOrder (myTree, tmp -> prev) == true );
		{
			return (true);
		}
	}
	return (false);
}
// For the first call in main. The follower must be the root node
binaryTree * obtainBinaryNode ( binaryTree * myTree, int pointsValue, Object * follower,  Object * root, Object **thatNode);
	{
		Object * tmp	= NULL;
		Object * tmp2	= NULL;
		Object * tmp3 	= NULL;
		
		tmp2			= follower; 
		tmp				= root;
		if (tmp == NULL)
		{
			return (myTree)
		}
		if ( pointsValue > tmp -> points)
		{
			myTree = obtainBinaryNode (myTree, pointsValue, tmp,  tmp -> next, **thatNode);
		}
		if ( pointsValue < tmp -> points)
		{
			myTree = obtainBinaryNode (myTree, pointsValue, tmp , tmp -> prev, **thatNode);
		}
// Cases where we could have the value!
// Leaf case. No children.
		if ( pointsValue == tmp -> points)	
			{
				if ( tmp -> next == NULL && tmp -> prev == NULL)
				{
// If its not the root node then disconnect the node.
					if ( tmp != myTree->root)
					{
						**thatNode = tmp;
						if (tmp2 -> next == tmp)
						{
							tmp2 -> next = NULL;
						}
						if (tmp2 -> prev == tmp)
						{
							tmp2 -> prev = NULL;
						}
					}
					else
					{
// If it is the root node then set myTree -> root to NULL;
						**thatNode = tmp;
						myTree -> root = NULL;
					}
		
					return (myTree);
				}	
// Two child case.  I FORGOT TO COMMENT MY CODE.
				if ( tmp -> next != NULL && tmp -> prev != NULL)
				{
// If it is not the root node then continue
					if ( tmp != myTree -> root)
					{
				 		**thatNode = tmp;
//tmp2 is following tmp. This means that tmp must be prev.
						if (tmp2 -> prev == tmp)
						{
//Connect tmp2 -> prev to tmp -> next.
							tmp2 -> prev 	= tmp -> next;
							tmp -> next 	= NULL;
							tmp3 			= tmp2 -> prev;
// Once that happens we want the lowest depth of tmp2 -> prev
							while (tmp3 -> prev != NULL;)
							{
								tmp3 = tmp3 -> prev;
							}
// Once we are at the lowest depth we can connect tmp3 -> prev to tmp ->prev.
								tmp3 -> prev = tmp -> prev;
								tmp -> prev = NULL;
						}
//tmp2 is following tmp. This means that
						if (tmp2 -> next == tmp)
						{
							tmp2 -> next   	= tmp -> prev;
							tmp  -> prev 	= NULL;
							tmp3			= tmp2 -> next;
							while (tmp3 -> next != NULL)
							{
								tmp3 = tmp3 -> next;
							}	
							tmp3 -> next 	= tmp -> next 
							tmp -> next 	= NULL;
						}
					}
// This happens if tmp is the root note.
					else 
					{
						**thaNode = tmp;
						tmp3 	  = tmp -> next;
						while (tmp3 -> prev != NULL)
						{
							tmp3 	= tmp3 -> prev;
						}
							
				return (myTree);
				}
	
// Only 1 branch scenario.		
		








#endif //BINARYTREE_H_

