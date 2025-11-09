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
binaryTree * obtainBinaryNode ( binaryTree * myTree, int pointsValue, Object * follower,  Object * root, Object **thatNode)
	{
		Object * tmp	= NULL;
		Object * tmp2	= NULL;
		Object * tmp3 	= NULL;
		bool success	= false;
		tmp2			= follower; 
		tmp				= root;
		if (tmp == NULL)
		{
			return (myTree);
		}
// Look right if greater. If successful. End the recursion.
		if ( pointsValue > tmp -> points)
		{
			myTree = obtainBinaryNode (myTree, pointsValue, tmp,  tmp -> next, &(*thatNode));
			if (success = true)
				{
					return (myTree);
				}
		}
// Look left is smaller or equal. If successful. End the recursion.
		if ( pointsValue < tmp -> points)
		{
			myTree = obtainBinaryNode (myTree, pointsValue, tmp , tmp -> prev, &(*thatNode));
			if ( success = true)
				{
					return (myTree);
				}
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
						(*thatNode) = tmp;
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
						(*thatNode) = tmp;
						myTree -> root = NULL;
					}
					success = true;
					return (myTree);
				}	
// Two child case.  I FORGOT TO COMMENT MY CODE.
				if ( tmp -> next != NULL && tmp -> prev != NULL)
				{
// If it is not the root node then continue
					if ( tmp != myTree -> root)
					{
						(*thatNode) = tmp;
//tmp2 is following (*thatNode). This means that (*thatNode) must be prev.
						if (tmp2 -> prev == (*thatNode))
						{
//Connect tmp2 -> prev to tmp -> next.
							tmp2 -> prev 				= (*thatNode) -> next;
							(*thatNode)		 -> next 	= NULL;
							tmp3 						= tmp2 -> prev;
// Once that happens we want the lowest depth of tmp2 -> prev
							while (tmp3 -> prev != NULL)
							{
								tmp3 = tmp3 -> prev;
							}
// Once we are at the lowest depth we can connect tmp3 -> prev to (*thatNode) -> prev.
								tmp3 -> prev 			= tmp -> prev;
								(*thatNode)	-> prev		= NULL;
						}
						if (tmp2 -> next == (*thatNode))
						{
							tmp2 -> next   	= tmp -> prev;
							(*thatNode)  -> prev 	= NULL;
// Go to the lowest depths of tmp2 -> next with tmp3
							tmp3			= tmp2 -> next;
							while (tmp3 -> next != NULL)
							{
								tmp3 = tmp3 -> next;
							}	
// Once at the lowest depth connect tmp3 -> next to *thatNode -> next and set *thatNode -> next to NULL
							tmp3 -> next 				= (*thatNode) -> next; 
							(*thatNode)	-> next 		= NULL;
						}
					success = true;
					return (myTree);
					}
// This happens if (*thatNode) is the root note.
					else 
					{
						(*thatNode) = tmp;
						tmp3 	  = (*thatNode) -> next;
// Get the lowest depth.
						while (tmp3 -> prev != NULL)
						{
							tmp2 	= tmp3;
							tmp3 	= tmp3 -> prev;
						}
// Moving pointers around.
						tmp2 -> prev = NULL;
						tmp2 		 = tmp -> next;
						myTree -> root = tmp3;
						tmp3   -> prev = tmp -> prev;
						(*thatNode)    -> prev = NULL;
						(*thatNode)    -> next = NULL;
// Lowest depth going to the right from tmp3 and then connect it to tmp2.
						while ( tmp3 -> next != NULL)
						{
							tmp3 = tmp3 -> next;
						}
						tmp3   -> next = tmp2;
					}
					return (myTree);
				}

	}
}
// Only 1 branch scenario.		
		








#endif //BINARYTREE_H_

