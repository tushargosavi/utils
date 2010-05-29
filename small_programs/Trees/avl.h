#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

#include <mytree.h>

class AVLTree : public Tree {

private :
	inline int rotate(Node **root, int dir);
	int doubleRotate(Node **root, int dir);
	int rebalnce(Node **root, int dir);
	int addNode(Node **root, int key);

public :
	void addNode(int key);
	Node *removeNode(int key);
};

#endif

