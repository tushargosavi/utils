#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <mytree.h>

using namespace std;

Node* Tree::search(int key)
{
	Node *temp = root;
	int dir;

	while (temp != NULL && temp->data != key) 
	{ 
		dir = temp->data < key;
		temp = temp->child[dir];
	}	
	return temp;
}

#define MAX(a, b) ( ((a) < (b)) ? (b) : (a))

int Tree::height()
{
	return height(this->root);
}

int Tree::height(Node *root)
{
	if (root == NULL) return 0;
	return (1 + (MAX( height(root->child[0]), height(root->child[1]))));
}

int Tree::count()
{
	return count(this->root);
}

int Tree::count(Node *node) 
{
	if (node == NULL) return 0;
	return (1 + count(node->child[0]) + count(node->child[1]));
}

void Tree::inorderTraverse(Node *root)
{
	if (! root) return;
	inorderTraverse(root->child[0]);
	cout << root->data << " ";
	inorderTraverse(root->child[1]);	
}

void Tree::preorderTraverse(Node *root)
{
	if (! root) return;
	cout << root->data << " ";
	inorderTraverse(root->child[0]);
	inorderTraverse(root->child[1]);	

}

void Tree::postorderTraverse(Node *root)
{
	if (! root) return;
	inorderTraverse(root->child[0]);
	inorderTraverse(root->child[1]);	
	cout << root->data << " ";
}

/* Display the tree in graphical interface */
void Tree::display(char *filename)
{
	FILE *fout = fopen(filename, "w");
	int status;
        int pid;

        if (fout == NULL) return;
        fprintf(fout, "digraph { \n");
        inorderPrint(root, fout);
        fprintf(fout, "}\n");
        fclose(fout);

        if (pid = fork()) {
                // waitpid(pid, &status, 0);
        }else {
                displayGraph(filename);
        }
}


/* This function will be called by child proces */
void Tree::displayGraph(char *filename)
{
        char psfile[256];
        char psfile1[256];
        char path[255];
        int pid;
	int status;

        sprintf(psfile,"%s.ps", filename);
        if (pid = fork()) {
                waitpid(pid, &status, 0);
                if (psfile[0] != '/') {
                        getcwd(path, 255);
                        sprintf(psfile1, "%s/%s", path, psfile);
                        strcpy(psfile, psfile1);
                }
                sleep(1);
                execl("/usr/bin/gv", "gv", psfile, NULL);
        }
        else {
                execl("/usr/bin/dot", "dot" , "-Tps", "-o", psfile, filename, NULL);
        }
}

Node* Tree::inorderPrint(Node *node, FILE *fout)
{
        Node *node1 = NULL;
        if (node == NULL) return NULL;

	fprintf(fout, "%d [label=\"%d, %d\"]\n", node->data, node->data, node->bf);
        node1 = inorderPrint(node->child[0], fout);
        if (node1) fprintf(fout, "%d -> %d [label=\"L\"];\n", node->data, node1->data);
        node1 = inorderPrint(node->child[1], fout);
        if (node1) fprintf(fout, "%d -> %d [label=\"R\"];\n", node->data, node1->data);
        return node;
}

void Tree::clear()
{
	clear(root);
	root = NULL;
}


void Tree::clear(Node *root)
{
	if (root == NULL) return;
	clear(root->child[0]);
	clear(root->child[1]);
	delete root;
}


