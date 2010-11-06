#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"
#include "parser.h"
#include "object.h"

Object *call_function(node_t *, node_t *);
void log(const char *fmt, ...);

struct symbol_table {
	char *name;
	Object *value;
	struct symbol_table *next;
};

struct symbol_table *symbol_head = NULL;
struct symbol_table *add_symbol(char *name, Object *value);
struct symbol_table *search_symbol(char *name);

Object *ret_value;

Object *ex(node_t *p)
{
	Object *value, *idx, *idx2, *arr;
	struct symbol_table *sym;
	Object *func_node, *arg_node;
	int i, n;
	char *name;

	print_node(p);
	if (!p) return;
	/* log("Executing node type=%d\n", p->type); */
	switch (p->type) {
		case typeIntConst :
			return create_int_obj(p->con.value);
		case typeStrConst :
			return create_str_obj(p->con.str);
		case typeChrConst :
			return create_char_obj(p->con.value);
		case typeArray :
			return create_arr_obj(ex(p->arr.value));
		case typeID :
			sym = search_symbol(p->id.name);
			if (sym) return sym->value;
			else return create_int_obj(0);
		case typeFuncCall :
			func_node = get_function(p->func.name);
			arg_node = ex(p->func.arg);
			return call_function(func_node, arg_node);
		case typeOpr:
			switch (p->opr.oper) {
				case ',' :
					value = append_array_obj(ex(p->opr.op[0]),
									 ex(p->opr.op[1]));
					return value;
				case '[' : 
					sym = search_symbol(p->opr.op[0]->id.name);
					idx = ex(p->opr.op[1]);
					if (sym && idx && p->opr.nops == 2)
						return array_access(sym->value, idx);
					else if (p->opr.nops = 3) {
						idx2 = ex(p->opr.op[2]);
						if (idx2) 
							return array_range(sym->value, idx, idx2);
					}
					return NULL;
				case ']' :
					idx = ex(p->opr.op[1]);
					if (idx != NULL && p->opr.nops == 2)
						return array_access(ex(p->opr.op[0]), idx);
					if (p->opr.nops == 3) {
						idx2 = ex(p->opr.op[2]);
						return array_range(ex(p->opr.op[0]), idx, idx2);	
					}
					return NULL;
				case WHILE :
					while (get_int(ex(p->opr.op[0]))) {
						value = ex(p->opr.op[1]);
						if (value == BREAK) {
							value = NULL;
							break;
						} else if (value == RETURN) {
							return ret_value;
						}
					}
					return value;
				case FOR :
					ex(p->opr.op[0]);
					while (get_int(ex(p->opr.op[1]))) {
						value = ex(p->opr.op[3]);
						if (value == BREAK) {
							value = NULL;
							break;
						} else if (value == RETURN) {
							return ret_value;
						}
						ex(p->opr.op[2]);
					}
					return value;
				case FOREACH :
					arr = ex(p->opr.op[1]);
					name = p->opr.op[0]->id.name;
					n = length(arr);
					for (i=0; i < n; i++) {
						add_symbol(name,
								array_access(arr,
										create_int_obj(i)));
						value = ex(p->opr.op[2]);
						if (value == BREAK) {
							value = NULL;
							break;
						} else if (value == RETURN) {
							return ret_value;
						}
					}
					return value;
				case BREAK:
					printf("executing break request\n");
					return BREAK;
				case CONTINUE :
					return CONTINUE;
				case RETURN :
					if (p->opr.nops == 1) {
						ret_value = ex(p->opr.op[0]);
					} else {
						ret_value = NULL;
					}
					return RETURN;
				case IF :
					if (get_int(ex(p->opr.op[0])))
						value = ex(p->opr.op[1]);
					else if (p->opr.nops > 2)
						value = ex(p->opr.op[2]);
					return value;
				case PRINT :
					value = ex(p->opr.op[0]);
					print_object(value);
					return value;
				case ';' :
					value = ex(p->opr.op[0]);
					if (value == RETURN || value == BREAK || value == CONTINUE)
						return value;
					return ex(p->opr.op[1]);
				case '=' :
					value = ex(p->opr.op[1]);
					add_symbol(p->opr.op[0]->id.name,
						value);
					return value;
				case UMINUS : 
					return minus(ex(p->opr.op[0]));
				case '+' :
					return apply_operator("+",
						   ex(p->opr.op[0]),
						   ex(p->opr.op[1]));
				case '-' :
					return apply_operator("-",
						   ex(p->opr.op[0]),
						   ex(p->opr.op[1]));
				case '*' :
					return apply_operator("*",
						   ex(p->opr.op[0]),
						   ex(p->opr.op[1]));
				case '/' :
					return apply_operator("/",
						   ex(p->opr.op[0]),
						   ex(p->opr.op[1]));
				case '<' :
					return apply_operator("<",
						   ex(p->opr.op[0]),
						   ex(p->opr.op[1]));
				case '>' :
					return apply_operator(">",
						   ex(p->opr.op[0]),
						   ex(p->opr.op[1]));
				case GE :
					return apply_operator(">=",
						   ex(p->opr.op[0]),
						   ex(p->opr.op[1]));
				case LE :
					return apply_operator("<=",
						   ex(p->opr.op[0]),
						   ex(p->opr.op[1]));
				case EQ :
					return apply_operator("==",
						   ex(p->opr.op[0]),
						   ex(p->opr.op[1]));
				case NE :
					return apply_operator("!=",
						   ex(p->opr.op[0]),
						   ex(p->opr.op[1]));
			}
	}
	return 0;
}

struct symbol_table *add_symbol(char *name, Object *value)
{
	struct symbol_table *ptr = search_symbol(name);
	if (ptr) {
		ptr->value = value;
		return ptr;
	}
	ptr = (struct symbol_table*)malloc(
			sizeof(struct symbol_table));
	ptr->name = strdup(name);
	ptr->value = value;
	ptr->next = symbol_head;	
	symbol_head = ptr;
	return ptr;	
}

struct symbol_table *search_symbol(char *name)
{
	struct symbol_table *ptr = symbol_head;
	while (ptr) {
		if (strcmp(ptr->name, name) == 0) 
			return ptr;
		ptr = ptr->next;
	}
	return NULL;
}

Object *call_function(node_t *code, node_t *arg)
{
	Object *value;
	add_symbol("arg", arg);
	value  = ex(code);
	return value;
}

