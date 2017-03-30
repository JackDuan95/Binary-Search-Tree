#include <stdio.h>
#include <stdbool.h>
#include <limits.h>									
#include "bst.h"

void bst_init( bst_t *tree ) 																											//initialize tree
{	
	tree->root = NULL;
	tree->size = 0;
}

void bst_destroy( bst_t *tree ) {																									//destroy tree
}

size_t bst_size( bst_t *tree ) 																										//return size of tree
{	
	return (tree->size);
}

bool bst_insert( bst_t *tree, S32 val ) 																					//insert node into tree
{
	bsn_t *key = (bsn_t*)malloc(sizeof(bsn_t));
	bsn_t *visitor = tree->root;
	key->val = val;	
	key->right = key->left = NULL;
	if (tree->root == NULL)																														//case where tree is empty
	{
		tree->root = key;
	 	tree->size ++;
	 	return true;
 	}
 	 
	while (val!= visitor->val)																												//condition to ensure val is not already in tree
	{
 		if (val < visitor->val)																														//insert in left subtree
 	 	{
 	 		if (visitor->left == NULL)
 	 	   	{
 	 	   		visitor->left = key;
 	 	   		tree->size++;
 	 	   		return true;
 	 	   	}
 	 	   	visitor = visitor->left;
 	 	}
		else 																																							//insert in right subtree
		{
			if (visitor->right == NULL)
			{
		  		visitor->right = key;
		  		tree->size++;
		  		return true;
			}
			visitor = visitor->right;
		}
	}
 	return false;
}

S32 bst_min( bst_t *tree ) 																													//return minimum value in tree
{	
	bsn_t *visitor = tree->root;
	if (tree->root == NULL)
	{
		return INT_MAX;
	}
	while (visitor->left !=NULL)
	{
		visitor = visitor->left;
	}
 	return visitor->val;
}

S32 bst_max( bst_t *tree ) 																													//return maximum value in tree
{	
	bsn_t *visitor = tree->root;
	if (tree->root == NULL) 
	{
		return INT_MIN;
	}
	while (visitor->right !=NULL)
		{
		visitor = visitor->right;
		}
 	return visitor->val;
	}

bool bst_erase_nochild ( bst_t *tree, S32 val, bsn_t *parent, bsn_t *visitor )				//erase node with no child
{
	if (visitor == tree->root) 																														//erase root node
	{
		tree->root = NULL;
	}
	else if (parent->left == visitor) 																										//erase node in left subtree
	{
		parent->left = NULL;
	}
	else 																																									//erase node in right subtree
	{
		parent->right = NULL;
	}
	tree->size --;
	return true;
} 

bool bst_erase_onechild_left ( bst_t *tree, S32 val, bsn_t *parent, bsn_t *visitor )	//erase node with one left child
{
	if (visitor == tree->root) 																														//erase root node
	{
		tree->root = tree->root->left;
	}
	else if (parent->left == visitor) 																										//erase node in left subtree
	{
		parent->left = visitor->left;
	}
	else 																																									//erase node in right subtree
	{
		parent->right = visitor->left;
	}
	tree->size --;
	return true;
}

bool bst_erase_onechild_right ( bst_t *tree, S32 val, bsn_t *parent, bsn_t *visitor )	//erase node with one right child
{
	if (visitor == tree->root) 																															//erase root node
	{
		tree->root = tree->root->right;
	}	
	else if (parent->right == visitor) 																											//erase node in right subtree
	{
		parent->right = visitor->right;
	}
	else 																																										//erase node in left subtree
	{
	parent->left = visitor->right;
	}
	tree->size --;
	return true;
}

bool bst_erase_twochild ( bst_t *tree, S32 val, bsn_t *parent, bsn_t *visitor )				//erase node with two children
{
bsn_t *smallest = visitor->right;
		parent = smallest; 
		while (smallest->left != NULL)  																										//traverses "smallest" until smallest value in right subtree is found
		{
			parent = smallest;
			smallest = smallest->left;
		}
		if (smallest->right == NULL)																												//if smallest right has no child
		{
		parent->left = NULL;
		visitor->val = smallest->val;
			if (visitor->right == smallest) 																										//if smallest equal to visitor right (immediate right child)
			{
				visitor->right = NULL;
			}
		}
		else 																																								//if smallest right has child
		{
			if (parent == smallest) 																														//if node's right child has no left child
			{
				visitor->right = parent->right;
				visitor->val = parent->val;
			}
			else 																																								//if node's right child has left child
			{
				parent->left = smallest->right;
				visitor->val = smallest->val;
			}
		}
		tree->size --;
		free(smallest);
		smallest = NULL;
		return true;
}	
	
bool bst_erase( bst_t *tree, S32 val ) 																									//erase tree
{	
	bsn_t *visitor = tree->root;
	bsn_t *parent = visitor;
	bool reached = false;
	if (tree->size == 0) 																																		//if tree is empty
	{
		return false;														
	}
	while (visitor->val != val && (visitor->left!= NULL || visitor->right!= NULL)) 					//gets visitor to correct node in tree
	{
        parent = visitor;
        if (val < visitor->val) 
				{
					visitor = visitor->left;
				}
        else 
				{
					visitor = visitor->right;
				}
	}
	if (val == visitor->val) 																																//val is found in tree											
	{
		reached = true;
	}
	if (!reached)
	{
		return false; 																																				//val is not found in tree
	}
	if (visitor->left == NULL && visitor->right == NULL)																		//node has no child
	{
		bst_erase_nochild ( tree, val, parent, visitor );
	}
	else if (visitor->left!= NULL && visitor->right == NULL)																//node has left child
	{
		bst_erase_onechild_left ( tree, val, parent, visitor );
	}      
	else if (visitor->left == NULL && visitor->right != NULL)																//node has right child
	{
		bst_erase_onechild_right ( tree,  val, parent, visitor );
	}      
	else																																										//node has two children
	{
		bst_erase_twochild ( tree,  val, parent, visitor);
	}
	visitor = NULL;
  parent = NULL;
  return true;
}
		  
