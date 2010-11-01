#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "node.h"

void log(const char *, ...);
node_t* con(int value)
{
	node_t *p;
	size_t node_size;
	if ((p = (node_t*)malloc(sizeof(node_t))) == NULL)
		yyerror("out of memory");
	p->type = typeIntConst;
	p->con.value = value;
	log("creating const node=%d ptr=%p\n", value, p);
	return p;
}

node_t* strcon(char *str)
{
	node_t *p;
	if ((p = (node_t*)malloc(sizeof(node_t))) == NULL)
		yyerror("out of memory");
	p->type = typeStrConst;
	p->con.str = strdup(str);
	log("creating str node=%s ptr=%p\n", str, p);
	return p;
}

node_t *charcon(char value)
{
	node_t *p;
	if ((p = (node_t*)malloc(sizeof(node_t))) == NULL)
		yyerror("out of memory");
	p->type = typeChrConst;
	p->con.value = value;
	log("creating char node=%d ptr=%p\n", value, p);
	return p;
}

node_t *arrnode(node_t *node)
{
	node_t *p;
	if ((p = (node_t*)malloc(sizeof(node_t))) == NULL)
		yyerror("out of memory");
	p->type = typeArray;
	p->arr.value = node;
	log("creating array node=%p ptr=%p\n", node, p);
	return p;
}

node_t *id(char *name)
{
	node_t *p;

	/* log("creating id node name=%s\n", name);	*/
	p = (node_t*)malloc(sizeof(node_t));
	if (!p) {
		yyerror("out of memory");
	}
	p->type = typeID;
	p->id.name = strdup(name);
	log("creating id node :%s %p\n", name, p);
	return p;
}

node_t *opr(int oper, int nops, ...)
{
	va_list ap;
	node_t *p;
	int i = 0;
	int nodeSize;

	/*
	log("creating opr node %d %d",	
		oper, nops);
	*/

	nodeSize = sizeof(node_t) + (nops - 1) * 
				   sizeof(node_t*);
	if ((p = (node_t*)malloc(nodeSize)) == NULL) {
		yyerror("out of memory");
	}

	p->type = typeOpr;
	p->opr.oper = oper;
	p->opr.nops = nops;
	va_start(ap, nops);
	for (i=0; i < nops; i++)
		p->opr.op[i] = (node_t*)va_arg(ap, node_t*);
	va_end(ap);
	log("creating opr node %d %d %p\n", oper, nops, p);
	return p;
}

void freeNode(node_t *p) {
	int i;

	if (!p) return;
	switch (p->type) {
		case typeOpr :
			for (i=0; i < p->opr.nops; i++) 
				freeNode(p->opr.op[i]);
			break;
		case typeID :
			free(p->id.name);
			break;
	}
	free(p);
}

void
print_node(node_t *p)
{
	int i=0;
	log("node %p type=%d ", p, p->type);
	switch(p->type) {
		case typeIntConst :
			log("value=%d\n", p->con.value);
			break;
		case typeStrConst :
			log("value=%s\n", p->con.str);
			break;
		case typeChrConst :
			log("value:%c\n", p->con.value);
			break;
		case typeArray :
			log("array :nodep=%p\n", p->arr.value);
			break;
		case typeID :
			log("id :%s\n", p->id.name);
			break;
		case typeOpr :
			log("%c %d [", p->opr.oper, p->opr.oper);
			for(i =0; i<p->opr.nops; i++ )
			{
				log("%p ", p->opr.op[i]);
			}
			log("]\n");
			break;
	}
}

