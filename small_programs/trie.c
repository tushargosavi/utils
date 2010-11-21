#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  char data;
  struct node *link[26];
}node_t;


void add_str(node_t **trie, char *str);
int search_str(node_t *trie, char *str);
node_t *alloc_node();
int idx(int a);

int main(int argc, char **argv)
{
  node_t *trie = NULL;
  char str[1024];
  char command[20];
  int found;

  while (1) {
    printf("> ");
    scanf("%s", command);
    if (strcmp(command, "add") == 0) {
      scanf("%s", str);
      add_str(&trie, str);
      printf("value of new  trie :%p\n", trie);
    }
    if(strcmp(command, "search") == 0) {
      scanf("%s", str);
      found = search_str(trie, str);
      if (found) {
	printf("string found in database");
      }	else {
	printf("string not found in the database");
      }
    }
  }
}

void add_str(node_t **trie, char *str)
{
  node_t *ptr;
  if (!(*trie)) {
    ptr =  alloc_node();
    *trie = ptr;
  }

  ptr = *trie;

  while (*str) {
    if (!(ptr->link[idx(*str)])) {
      printf("allocating node for : %c\n", *str);
      ptr->link[idx(*str)] = alloc_node();
    }
    ptr = ptr->link[idx(*str)];
    str++;
  }
}

int search_str(node_t *trie, char *str)
{
  node_t *ptr = trie;
  while (*str) {
    if (ptr->link[idx(*str)]) ptr = ptr->link[idx(*str)];
    else break;
    str++;
  }
  if (*str) return 0;
  else return 1;
}

node_t *alloc_node() {
  node_t *ptr = (node_t*)malloc(sizeof(node_t));
  memset(ptr, 0, sizeof(node_t));
  return ptr;
}

int idx(int n)
{
  if (n >= 'a' && n <= 'z') return (n - 'a');
  if (n >= 'A' && n <= 'Z') return (n - 'A' + 26);
  if (n >= '0' && n <= '9') return (n - '0' + 52);
  if (n == 0) return 63;
}
