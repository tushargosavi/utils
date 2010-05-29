#ifndef BST_TREE_H
#define BST_TREE_H

#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

#include <mytree.h>

class BstTree : public Tree {
public :
	void addNode(int key);
	Node *removeNode(int key);
};

#endif

