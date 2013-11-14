#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <dequeue>

struct Node {
  int data;
  Node *left;
  Node *right;

  Node(int a):data(a), left(NULL), right(NULL) {}
};

void insert_bst(Node **root, int data) 
{
  Node *new_node = new Node(data);
  Node **node = root;
  while (*node) {
    if (data < (*node)->data)
      node = &(*node)->left;
    else
      node = &(*node)->right;
  }
  *node = new_node;
}

void print_bst(Node *root) {
  if (root == NULL) return;
  print_bst(root->left);
  printf("%d " , root->data);
  print_bst(root->right);
}

/*
void print_tree(Node *node) {
  dequeue<Node*> queue;
  queue.push_back(node);
  while(!queue.empty()) {
    Node *item = queue.front();
    queue.pop_front();
    
    
  }
}
*/


/* Approach
 * generate list for left tree call it as l1
 * generate list for right tree call it as l2
 * sandwitch node between l1 and l2 = l1 + node + l2
 * keep doing it recursively.
 */
void bst2dll(Node *node, Node **head, Node **tail) {

  Node *h1,*t1,*h2,*t2;
  // If this is the NULL node , then do not return any list
  if (node == NULL) {
    if (head) *head = NULL;
    if (tail) *tail = NULL;
    return;
  }
  
  // recursively generate list for left and right tree
  bst2dll(node->left, &h1, &t1);
  bst2dll(node->right, &h2, &t2);

  // add the node between two lists.
  node->left = t1; if(t1) t1->right = node; 
  node->right = h2; if(h2) h2->left = node;
 
  // If right and left tree are empty then
  // return tree with one element only
  // else return head or left list as new head
  //      and tail of right list as new tail.
  if (head) *head = h1? h1 : node;
  if (tail) *tail = t2? t2 : node;
}

void print_list(Node *head) {
  while (head) {
    printf("%d ", head->data);
    head = head->right;
  }
  printf("\n");
}

int main(int argc, char **argv)
{
  Node *root = NULL;
  Node *dl, *tl;
  int v;
  for(int i = 0; i < 10; i++) {
    v = rand() % 100;
    printf("%d ", v);
    insert_bst(&root, v);
  }
  printf("\n");
  print_bst(root);
  printf("\n");
  bst2dll(root, &dl, &tl);
  printf("%p %p\n", dl, tl);
  print_list(dl);
  return 0;
};

