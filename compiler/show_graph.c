#include <stdio.h>
#include <stdlib.h>

#include "node.h"
#include "parser.h"

int graph_count = 0;

void ex(node_t *p)
{
	printf("digraph g%d {\n", graph_count );
	traverse_tree(p);
	printf("}\n");
	graph_count++;
}

void traverse_tree(node_t *p)
{
	int i =0;
	if (p->type == typeOpr ) {
		printf("node%p [label=%d]\n", p, p->opr.oper);
		for (i=0; i<p->opr.nops; i++) 
			printf("node%p -> node%p\n", p, p->opr.op[i]);
		for (i=0; i < p->opr.nops; i++)
			traverse_tree(p->opr.op[i]);
	}

	switch(p->type) {
		case typeIntConst :	
			printf("node%p [label=int]\n", p); break;
		case typeChrConst :
			printf("node%p [label=char]\n", p); break;
		case typeStrConst: 
			printf("node%p [label=str]\n", p); break;
		case typeArray :
			printf("node%p [label=arr]\n", p); break;
	}
}

