
#include "node.h"
#include "parser.h"

struct keyword_ent {
	char *name;
	int	token;
};

typedef struct keyword_ent keyword_ent_t;

keyword_ent_t keyword_tbl[] = {
	{ "while", WHILE },
	{ "if", IF },
	{ "else", ELSE },
	{ "print", PRINT },
	{ "function", FUNCTION },
};

int is_keyword(char *yytext)
{
	int i = 0;
	for(i=0; i < sizeof(keyword_tbl)/sizeof(keyword_ent_t); i++) {
		if (strcmp(yytext, keyword_tbl[i].name) == 0) {
			return keyword_tbl[i].token;
		}
	}
	return 0;
}
