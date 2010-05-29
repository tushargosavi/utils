#include <iostream>

#include <mytree.h>
#include <bst.h>
#include <avl.h>

Tree *tree = NULL;
int max_value = 1000;

struct command {
        const char *command;
	const char *help;
        void (*func)(void);
};

/* Command functions */
void create_cmd();
void add_random_cmd();
void addn_node_cmd();
void add_node_cmd();
void del_node_cmd();
void search_cmd();
void display_node_cmd();
void display_height_cmd();
void display_count_cmd();
void help_cmd();
void setmax_cmd();
void quit_cmd();
void clear_cmd();
int check_tree();

struct command commands[] = {
	{ "create", "Create a tree", create_cmd },
        { "rand", "Add random nodes to the tree", add_random_cmd },
        { "add", "Add node to the tree", add_node_cmd },
        { "addn", "Add node to the tree", addn_node_cmd },
        { "del", "Remove a node from tree", del_node_cmd },
        { "display", "Display tree using gv", display_node_cmd },
        { "height", "Display height of the tree ", display_height_cmd },
        { "count", "Display Number of element of tree ", display_count_cmd },
        { "search", "search a key ", search_cmd },
	{ "help", "Show this message", help_cmd },
	{ "max", "set max value in random addition", setmax_cmd },
        { "quit", "Quit", quit_cmd },
	{ "clear", "Clear tree", clear_cmd },
        { NULL }
};


/* Tree test functions */
void add_random_nodes(int n, int max_value);

int main(int argc, char *argv[])
{
        char command[255];
        int i;

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

int check_tree()
{
	if (tree == NULL) {
		cout << "tree is set ot null, initialize it using create command" << endl;
		return 0;
	}
	return 1;
}

void create_cmd()
{
	char type[80];

	scanf("%s", type);
	if (strcmp(type, "bst") == 0) 
		tree = new BstTree();

	if (strcmp(type, "avl") == 0)
		tree = new AVLTree();

	/* default to Bst Tree */
	if (tree == NULL) 
		tree = new BstTree();

	/* These trees are not implemented yet.
	if (strcmp(type, "rb") == 0)
		tree = new RbTree();
	if (strcmp(type, "avl") == 0)
		tree = new AVLTree();
	*/
}

void add_random_cmd()
{
        int n;
        scanf("%d", &n);

	if (check_tree() == 0) return;
        add_random_nodes(n, max_value);
}

void addn_node_cmd()
{
	int count;
	int key;
	int i;

	scanf("%d", &count);

	if (check_tree() == 0) return;
	for (i=0; i< count ; i++) {
		scanf("%d", &key);
		tree->addNode(key);
	}
}

void add_node_cmd()
{
        int n;
        scanf("%d", &n);

	if (check_tree() == 0) return;
        tree->addNode(n);
}

void del_node_cmd()
{
        int n;
        scanf("%d", &n);

	if (check_tree() == 0) return;
	tree->removeNode(n);
}

void display_node_cmd()
{
        char filename[255];
        scanf("%s", filename);

	if (check_tree() == 0) return;
        tree->display(filename);
}

/* Add randmon number of nodes in the tree */
void add_random_nodes(int n, int max_value)
{
        int i=0;
	int key=0;
	Node *node = NULL;
	int count=0;

        srand(time(NULL));

        for (i=0; i < n ; i++) {
                key = 1 + (int) (max_value * (rand()/(RAND_MAX + 1.0)));
                node = tree->search(key);
                if (node == NULL) tree->addNode(key);
		else i--;
		printf("Added key =%d\n", key);
		if ((i % 100) == 0) {
			printf(".");
			fflush(stdout);
		}
        }
	printf("Done\n");
}

void display_height_cmd()
{
	printf("%d\n", tree->height());
	printf("left height =%d and right height=%d\n", 
		tree->height(tree->getRoot()->child[0]), 
		tree->height(tree->getRoot()->child[1]));
		
}


void display_count_cmd()
{
	printf("%d\n", tree->count());
}

void search_cmd()
{
	int key;
	Node *node;

	scanf("%d", &key);
	node = tree->search(key);
	if (node != NULL) {
		printf("fount key %d in tree\n", node->data);
	} else {
		printf("not fount key %d in tree\n", key);
	}
}

void clear_cmd()
{
	if (check_tree() == 0) return;
	tree->clear();
}

void help_cmd()
{
	int i=0;
	for (i=0; commands[i].command != NULL; i++) {
		cout << commands[i].command << "\t\t" << commands[i].help << endl;
	}
}

void setmax_cmd()
{
	int n;
	scanf("%d", &n);
	max_value = n;
}

void quit_cmd()
{
        exit(0);
}

