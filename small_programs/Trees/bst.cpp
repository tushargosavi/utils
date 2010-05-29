#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

#include <mytree.h>
#include <bst.h>

void BstTree::addNode(int key)
{
	Node **temp;
	int dir;

	if (root == NULL) {
		root = new Node(key);
		return;
	}
	
	temp = &root;
	while ( *temp) {
		dir = (*temp)->data < key;
		temp = &((*temp)->child[dir]);
	}
	*temp = new Node(key);
}


Node *BstTree::removeNode(int key)
{
	Node **temp;
	Node *replace;
	Node **node;
	Node *toret;
	int dir=0;

	temp = &root;
	while (*temp && (*temp)->data != key ) {
		dir = (*temp)->data < key;
		temp = &(*temp)->child[dir];
	}

	// If key not found then return
	if (*temp == NULL) return NULL;
	
	// store node to return	
	toret = *temp;

	if ( (*temp)->child[0] && (*temp)->child[1]) {
		// This is the complex case to handle, find max from the left subtree 
		// and then replace it with current node.
		node = &(*temp)->child[0];
		while ((*node)->child[1] != NULL) node = &(*node)->child[1];

		replace = *node;
		*node = (*node)->child[0];
		replace->child[0] = (*temp)->child[0];
		replace->child[1]= (*temp)->child[1];

		*temp= replace;


	} else {
		// Either both, or a child is NUL
		// Relace delted node with that child or NULL
		replace = (*temp)->child[0] ? (*temp)->child[0] : (*temp)->child[1];
		*temp = replace;
	} 
	return toret;
}

