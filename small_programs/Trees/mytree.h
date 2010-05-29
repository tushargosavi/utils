#ifndef MYTREE_H
#define MYTREE_H

#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;



class Node {
public :
	/* key for the node */
	int data;

	/* Balance factor used for AVL tree*/ 
	int bf ;

	/* left and right children, left children at index 0 
 	*  and right children is at index 1, that way we can calculate dir as (node->data < key) 
 	*  */
	Node *child[2];

public :
	/* Constructor for node,
 	* set data to passed values and child pointers to NULL
 	*/
	Node(int d) : data(d) { child[0] = child[1] = NULL; bf = 0; };
	~Node() { cout << "deleting node " << data << endl; }
};


class Tree {
protected :
	Node *root;

private :
        Node *inorderPrint(Node *, FILE *);
	void displayGraph(char *filename);
	int count(Node *node);
	virtual void clear(Node *);

public :

	// Contructor set root to NULL
	Tree():root(NULL) { };

	// return root pointer
	Node *getRoot() { return root; }

	virtual void addNode(int) = 0;
	virtual Node *removeNode(int) = 0;
	virtual Node *search(int);
	virtual void inorderTraverse(Node *);
	virtual void preorderTraverse(Node *);
	virtual void postorderTraverse(Node *);
	virtual void clear();
	virtual void display(char *filename);
	int height();
	int height(Node *node);
	int count();
};


#endif

