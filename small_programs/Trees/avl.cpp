#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

#include <mytree.h>
#include <avl.h>


#define MAX(a, b) (( a > b) ? a : b)
#define MIN(a, b) ((a > b) ? b : a)


int AVLTree::rotate(Node **root, int dir)
{
	Node *oldroot = *root;
	Node *pivot = (*root)->child[!dir];
	int heightChange = (pivot->bf == 0)? 0 : 1;	
	(*root)->child[!dir] = pivot->child[dir];
	pivot->child[dir] = *root;
	*root=pivot;

	if (dir == 0)  {
		oldroot->bf -= (1 + MAX(pivot->bf, 0));
		pivot->bf -= (1 - MIN(oldroot->bf, 0));
	} else  /* dir == RIGHT */  {
		oldroot->bf +=  (1 - MIN(pivot->bf, 0) );
		pivot->bf +=  (1 + MAX(oldroot->bf, 0));
	}

	return heightChange;
}


int AVLTree::doubleRotate(Node **root, int dir)
{
	rotate(&(*root)->child[!dir], !dir);
	rotate(root, dir);
	return 1;
}

/*
 * Node was added in one direction, we need to perform opposite rotation
 */
int AVLTree::rebalnce(Node **root, int dir)
{
	int bal = (dir == 0)? -1 : 1;
	Node *n;

	/* AVL property is invalidated because of addition on a node
 	*  in dir direction
 	*/	 
	if (abs((*root)->bf) > 1) {
		/* check the balance of oppisit child */
		n = (*root)->child[dir];
		if (n->bf == -bal) {
			/* Double rotation neede */
			cout << "calling AVLTree::doubleRotate" << (*root)->data << "  dir =" << !dir << endl;
			return doubleRotate(root, !dir); 
		} else  {
			/* Single rotation neede */
			cout << "calling AVLTree::rotate " << (*root)->data << "  dir =" << !dir << endl;
			return rotate(root, !dir);
		}
	}
	return 1;
}

int AVLTree::addNode(Node **root, int key)
{
	Node **temp;
	int dir;
	int change;
	int bal;

	if (*root == NULL) {
		*root = new Node(key);
		return 1;
	}

	dir = (*root)->data < key;
	change = addNode(&(*root)->child[dir], key);
	
	/* Hight change occur at subtree */
	if (change) {
		bal = (dir == 0)? -1 : +1;
		(*root)->bf += bal;
		cout << "setting bal of " << (*root)->data << " to " << (*root)->bf << endl;

		if ((*root)->bf == 0)
			return 0;

		if (abs((*root)->bf) > 1 ) {
			rebalnce(root, dir);
			return 0;
		}
	}
	return change;
}


void AVLTree::addNode(int key)
{
	addNode(&root, key);
}


Node *AVLTree::removeNode(int key)
{
	Node **temp;
	Node *replace;
	Node **node;
	Node *toret;
	int dir=0;
	Node **nstack[50];
	int dstack[50];
	int top =0;
	int node_idx =0;
	int done=0;

	temp = &root;
	while (*temp && (*temp)->data != key ) {
		dir = (*temp)->data < key;
		nstack[top] = temp;
		dstack[top++] = dir;
		temp = &(*temp)->child[dir];
	}

	node_idx = top;
	top ++;

	// If key not found then return
	if (*temp == NULL) return NULL;
	
	// store node to return	
	toret = *temp;

	if ( (*temp)->child[0] && (*temp)->child[1]) {
		// This is the complex case to handle, find max from the left subtree 
		// and then replace it with current node.
		node = &(*temp)->child[0];
		while ((*node)->child[1] != NULL) {
			nstack[top] = node;
			dstack[top++] = 1;
			node = &(*node)->child[1];
		}

		replace = *node;
		*node = (*node)->child[0];
		replace->child[0] = (*temp)->child[0];
		replace->child[1]= (*temp)->child[1];

		*temp= replace;

		/* update the stack and set balance factor of the replaced node */
		nstack[node_idx] = temp;
		dstack[node_idx] = 0;
		replace->bf = toret->bf;

	} else {
		// Either both, or a child is NUL
		// Relace delted node with that child or NULL
		dir = (*temp)->child[0] ? 0 : 1;
		replace = (*temp)->child[0] ? (*temp)->child[0] : (*temp)->child[1];
		*temp = replace;
		top --;
	} 

	top--;
	/*
	node = nstack[top];
	(*node)->bf = (dstack[top] == 0)? 1 : -1;
	*/
	done =0;
	while (top >= 0 && !done) {
		node = nstack[top];
		dir = dstack[top--];
		node_idx - (*node)->bf;
		(*node)->bf += (dir == 0)? 1 : -1;

		printf("key=%d bf=%d dir=%d index=%d\n", (*node)->data, (*node)->bf, dir, top+1); 	
		
		if (abs((*node)->bf) > 1 ) 
			done = !rebalnce(node, !dir);
		else {
			if ((abs(node_idx) > 0) && ((*node)->bf == 0))
				done = 0;
			else done =1;
		}

	}

	return toret;
}


