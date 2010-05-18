/*
============================================================================
Name        : skiplist.c
Author      : Tushar Gosavi
Version     :
Copyright   : GNU :)
Description : Hello World in C, Ansi-style
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct node {
	int data; /* key for the node */
	int level; /* level of node */
	struct node *link[1]; /* link pointers */
};

typedef struct node node_t;

node_t *header;

typedef struct skip_list {
	int max_level;
	int curr_level;
	float prob;
	node_t *header;
} skip_list_t;


/* initialize a skip list with max_level and probability as prob */
skip_list_t *init_skip_list(int max_level, float prob);
/* allocate a new node for skip_list */
node_t *alloc_node(skip_list_t *, int *);
int rand_level(float prob);

skip_list_t *init_skip_list(int max_level, float prob)
{
	skip_list_t *list = (skip_list_t*)malloc(sizeof(skip_list_t));
	int size = sizeof(node_t) + sizeof(node_t*) * (max_level);
	list->header = (node_t*)malloc(size);
	list->max_level = max_level;
	list->curr_level = 0;
	list->header->data = -1000;
	list->prob = prob;
	return list;
}


node_t *seach_list(skip_list_t *list, int key);
void add_key(skip_list_t *list, int key);
node_t *delete_key(skip_list_t *list, int key);
void print_list(skip_list_t *list, int n);

skip_list_t *list;


/* Command functions */
void add_random_cmd();
void addn_node_cmd();
void add_node_cmd();
void del_node_cmd();
void search_cmd();
void display_node_cmd();
void displayn_node_cmd();
void display_height_cmd();
void display_count_cmd();
void help_cmd();
void quit_cmd();
void add_random_nodes(int n, int max_value);


struct command {
	const char *command;
	const char *help;
	void (*func)(void);
};


struct command commands[] = {
	{ "rand", "Add random nodes to the list", add_random_cmd },
	{ "add", "Add node to the list", add_node_cmd },
	{ "addn", "Add node to the list", addn_node_cmd },
	{ "del", "Remove a node from tree", del_node_cmd },
	{ "display", "Display list", display_node_cmd },
	{ "level", "Display list at level n", displayn_node_cmd },
	{ "height", "Display current level of tree ", display_height_cmd },
	{ "count", "Display Number of element of tree ", display_count_cmd },
	{ "search", "search a key ", search_cmd },
	{ "help", "Show this message", help_cmd },
	{ "quit", "Quit", quit_cmd },
	{ NULL }
};

int main(int argc, char *argv[])
{
	char command[255];
	int i;

	list = init_skip_list(100, 0.5);

	while (1) {
		printf("> ");
		scanf("%s", command);
		for (i=0; commands[i].command != NULL; i++) {
			if (strcmp(command, commands[i].command) == 0) {
				commands[i].func();
				break;
			}
		}

		if (commands[i].command == NULL) {
			printf("Invalid command\n");
		}
	}
	return 0;
}


node_t *search_list(skip_list_t *list, int key) 
{
	node_t *ptr, *oldptr;
	int i;
	int hops =0;

	ptr = list->header;
	oldptr = ptr;
	for (i = list->curr_level -1; i >= 0; i--) {
		while (ptr->link[i] && ptr->link[i]->data < key) {
			ptr = ptr->link[i];
			hops++;
		}
	}
	printf("number of hops=%d\n", hops);
	/* check if node found or not */
	if (ptr->link[0] && ptr->link[0]->data != key) {
		return NULL;
	}
	return ptr->link[0];
}


int rand_level(float p)
{
	int level = 1;
	float r;

	r = 1 + (int) (1000 * (rand() / (RAND_MAX + 1.0)));
	r /= 1000;
	while (r < p && level < 1000) {
		level++;
		r = 1 + (int) (1000 * (rand() / (RAND_MAX + 1.0)));
		r /= 1000;
	}
	printf("returning random level as %d\n", level);
	return level;
}

node_t *alloc_node(skip_list_t *list, int *lvl)
{
	node_t *node;
	int size;
	node_t *header;
	int level;

	level = rand_level(list->prob);

	/* see if you have enough space in the header */
	if ( level > list->max_level) {
		/* we need to modify list header */
		size = sizeof(node_t) + sizeof(node_t*) * (level + 5);
		header = (node_t*)malloc(size);
		memset(header, 0, size);
		memcpy(list->header, header,
			sizeof(node_t) +
			sizeof(node_t*)* (list->max_level -1));
		free(list->header);
		list->header = header;
		list->max_level = level + 5;
	}

	size = sizeof(node_t) + sizeof(node_t*) * (level -1);
	node = (node_t*)malloc(size);
	memset(node, 0, size);
	printf("allocating level to %d\n", level);
	*lvl = level;
	return node;
}

void add_key(skip_list_t *list, int key)
{
	node_t **update;
	node_t *node;
	node_t *ptr;
	int size; 
	int i=0;
	int level;

	/* Allocate a node and decide a level for it */
	node = alloc_node(list, &level);
	node->data = key;

	size = sizeof(node_t*) * ((level > list->curr_level)?
			level : list->curr_level);
	update = (node_t**)malloc(size);
	memset(update, 0, size);

	ptr = list->header;
	for (i = list->curr_level -1; i >= 0; i--) {
		while (ptr->link[i] && ptr->link[i]->data < key) 
			ptr = ptr->link[i];
		update[i] = ptr;
	}

	if (level > list->curr_level)
		list->curr_level = level;

	/* Insert at this location */
	for (i = 0; i < level; i++) {
		if (update[i]) {
			node->link[i] = update[i]->link[i];
			update[i]->link[i] = node;
		} else {
			list->header->link[i] = node;
		}
	}
	free(update);
}


node_t *remove_key(skip_list_t *list, int key)
{
	node_t *node = NULL;
	node_t **update;
	node_t *ptr;
	int i=0;
	int size = sizeof(node_t*) * list->curr_level;

	update = (node_t**)malloc(size);
	memset(update, 0, size);

	ptr = list->header;
	for (i = list->curr_level -1; i >= 0; i--) {
		while (ptr->link[i] && ptr->link[i]->data < key) 
			ptr = ptr->link[i];
		update[i] = ptr;
	}

	node = update[0]->link[0];
	if (!node || node->data != key) {
		free(update);
		return NULL;
	}

	for (i=0; i < list->curr_level; i++) {
		if (update[i]->link[i] == node) {
			update[i]->link[i] = node->link[i];
		} else break;
	}

	for (i= list->curr_level -1; i >= 0; i--) {
		if (list->header->link[i] == NULL) list->curr_level --;
	}

	free(update);
	return node;
}


void print_list(skip_list_t *list, int n)
{
	node_t *ptr = NULL;
	if (n > (list->curr_level -1)) 
		return;
	ptr = list->header->link[n];
	while (ptr != NULL) {
		printf("%d ", ptr->data);
		ptr= ptr->link[n];
	}
	printf("\n");
}


/* interface functions */
void add_random_cmd() {
	int n;
	scanf("%d", &n);
	add_random_nodes(n, 1000);
}

void addn_node_cmd() {
	int count;
	int key;
	int i;

	scanf("%d", &count);

	for (i=0; i< count; i++) {
		scanf("%d", &key);
		add_key(list, key);
	}
}

void add_node_cmd() {
	int n;
	scanf("%d", &n);
	add_key(list, n);
}

void del_node_cmd() {
	int n;
	node_t *node;

	scanf("%d", &n);
	node = remove_key(list, n);
	if (node == NULL) {
		printf("node not found");
	}else {
		printf("node found");
	}
}

void display_node_cmd() {
	print_list(list, 0);	
}

void displayn_node_cmd() {
	int n;
	scanf("%d", &n);
	print_list(list, n);
}

/* Add randmon number of nodes in the tree */
void add_random_nodes(int n, int max_value) {
	int i=0;
	int key=0;

	srand(time(NULL));

	for (i=0; i < n; i++) {
		key = 1 + (int) (max_value * (rand()/(RAND_MAX + 1.0)));
		printf("adding key=%d\n", key);
		add_key(list, key);
	}
	printf("Done\n");
}

void display_height_cmd() {
	printf("%d\n", list->curr_level);
}

void display_count_cmd() {
	int count =0;
	node_t *ptr = list->header->link[0];
	while (ptr != NULL) {
		ptr= ptr->link[0];
		count ++;
	}
	printf("count=%d \n", count);
}

void search_cmd() {
	int key;
	node_t *node;

	scanf("%d", &key);
	node = search_list(list, key);
	if (node != NULL) {
		printf("fount key %d in tree\n", node->data);
	} else {
		printf("not fount key %d in tree\n", key);
	}
}

void help_cmd() {
	int i=0;
	for (i=0; commands[i].command != NULL; i++) {
		printf("%s \t\t%s\n", commands[i].command, commands[i].help);
	}
}

void quit_cmd() {
	exit(0);
}
