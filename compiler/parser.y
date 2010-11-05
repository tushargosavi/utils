%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"
#include "object.h"

void define_function(char *name, node_t *node);
%}

%union {
	unsigned int  intval;
	char *str;
	node_t *nodep;
}
	
%token <intval> INTEGER CHAR
%token <str> STRING
%token <str> IDENTIFIER
%token WHILE IF PRINT FUNCTION TWODOTS
%type  <nodep> expr stmt stmt_list arr_access array_def function function_call args
%nonassoc IFX
%nonassoc ELSE

%left GE LE EQ NE '>' '<' L_AND L_OR 
%left '+' '-' '&' '|' LEFT_SHIFT RIGHT_SHIFT
%left '*' '/'
%nonassoc UMINUS

%%

program:
	functions { main_loop(); }
	;

functions:
	functions function { }
	|
	;

function:
	FUNCTION IDENTIFIER '{' stmt_list '}' { define_function($2, $4); }
	|
	;

stmt:
	';'					{ $$ = opr(',', 2, NULL, NULL); }
	| expr ';'			{ $$ = $1 }
	| PRINT expr ';'	{ $$ = opr(PRINT, 1, $2); }
	| IDENTIFIER '=' expr ';' { $$ = opr('=', 2, id($1), $3); }
	| IDENTIFIER '[' expr ']' '=' expr ';' { $$ = opr('[', 3, $1, $3, $6); }
	| IDENTIFIER '=' '[' array_def ']' ';' { $$ = opr('=', 2, id($1), $4); }
	| WHILE '(' expr ')' stmt { $$ = opr(WHILE, 2, $3, $5); }
	| IF '(' expr ')' stmt %prec IFX { $$ = opr(IF, 2, $3, $5); }
	| IF '(' expr ')' stmt ELSE stmt { $$ = opr(IF, 3, $3, $5, $7); }
	| '{' stmt_list '}' { $$ = $2 }
	;

stmt_list:
	stmt		{ $$ = $1 }
	| stmt_list stmt  { $$ = opr(';', 2, $1, $2); }
	;

array_def:
	expr			     { $$ = arrnode($1); }
	| array_def ',' expr { $$ = opr(',', 2, $1, $3); }
	;

arr_access:
	| IDENTIFIER '[' expr ']' { $$ = opr('[', 2, id($1), $3); }
	| IDENTIFIER '[' expr TWODOTS expr ']' { $$ = opr('[', 3, id($1), $3, $5); }
	| arr_access '[' expr TWODOTS expr ']' { $$ = opr(']', 3, $1, $3, $5); }
	| arr_access '[' expr ']' { $$ = opr(']', 2, $1, $3); }
	;

function_call:
	IDENTIFIER '(' args ')'	   { $$ = function_callnode($1, $3); }
	;

args:
	expr			{ $$ = arrnode($1); }
	| args ',' expr	{ $$ = opr(',', 2, $1, $3); }
	;

expr:
	INTEGER			{ $$ = con($1) }
	| IDENTIFIER	{ $$ = id($1); }
	| STRING	{ $$ = strcon($1); }
	| CHAR		{ $$ = charcon($1); }
	| arr_access { $$ }
	| function_call { $$ }
	| '-' expr %prec UMINUS { $$ = opr(UMINUS, 1, $2); }
	| expr '+' expr	{ $$ = opr('+', 2, $1, $3); }
	| expr '-' expr { $$ = opr('-', 2, $1, $3); }
	| expr '*' expr { $$ = opr('*', 2, $1, $3); }
	| expr '/' expr { $$ = opr('/', 2, $1, $3); }
	| expr '<' expr	{ $$ = opr('<', 2, $1, $3); }
	| expr '>' expr { $$ = opr('>', 2, $1, $3); }
	| expr EQ expr  { $$ = opr(EQ, 2, $1, $3); }
	| expr LE expr  { $$ = opr(LE, 2, $1, $3); }
	| expr GE expr  { $$ = opr(GE, 2, $1, $3); }
	| expr '&' expr { $$ = opr('&', 2, $1, $3); }
	| expr '|' expr { $$ = opr('|', 2, $1, $3); }
	| expr L_AND expr { $$ = opr(L_AND, 2, $1, $3); }
	| expr L_OR expr  { $$ = opr(L_OR, 2, $1, $3); }
	| expr LEFT_SHIFT expr  { $$ = opr(LEFT_SHIFT, 2, $1, $3); }
	| expr RIGHT_SHIFT expr { $$ = opr(RIGHT_SHIFT, 2, $1, $3); }
	| '(' expr ')'			{ $$ = $2; }
	| '!' expr		{ $$ = opr('!', 1, $2); }
	;
%%

struct func_list {
	char *name;
	node_t *node;
	struct func_list *next;
};

struct func_list *func_list_head = NULL;

void define_function(char *name, node_t *node)
{	
	struct func_list *func = (struct func_list *)malloc(sizeof(struct func_list));
	func->name = strdup(name);
	func->node = node;
	if (func_list_head) {
		func->next = func_list_head;
		func_list_head = func;
	} else {
		func_list_head = func;
	}
}

node_t *get_function(char *name)
{
	struct func_list *tmp = func_list_head;
	while (tmp) {
		if (strcmp(tmp->name, name) == NULL) 
			return tmp->node;
		tmp = tmp->next;
	}
	return NULL;
}

void main_loop() {
	node_t *node;
	char command[128];
	char func_name[128];
	Object *obj;

	while (1) {
		printf("> ");
		scanf("%s", command);
		if (strcmp(command, "run") == 0) {
			scanf("%s", func_name);
			node = get_function(func_name);
			if (node!= NULL) {
				obj = ex(node);
				if (obj != NULL)
					print_object(obj);
			} else {
				printf("function %s not found\n", func_name);
			}
		}
		if (strcmp(command,"exit") == NULL) {
			exit(0);
		}
	}
}
