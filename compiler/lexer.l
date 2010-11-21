%{
#include <stdio.h>
#include <stdlib.h>

#include "node.h"
#include "parser.h"

char str_ptr[1024];

void yyerror(char *str);
void comment();
void read_str();
int is_keyword(char *name);

%}

DIGIT	[0-9]
LETTER	[a-zA-Z]

%%
\"	{
		read_str();
		yylval.str = str_ptr;
		return STRING; 
	}
"/*" {
		comment();
	}

"0x"{DIGIT}+ {
		yylval.intval = atoi(yytext);
		return INTEGER;
	}
{DIGIT}+	{
		yylval.intval = atoi(yytext);
		return INTEGER;
	}
[_a-zA-Z][_a-zA-Z0-9]* {
		if (is_keyword(yytext)) {
			return is_keyword(yytext);
		}
		yylval.str = strdup(yytext);
		return IDENTIFIER;
	}
[;+-/*=\[\]<>{}()&^%$@!] {
		return *yytext;
	}
"\.\."	{ return TWODOTS; }
">="	{ return GE; }
"<="	{ return LE; }
"=="	{ return EQ; }
"!="	{ return NE; }
"'"."'" {
		yylval.intval = *(yytext + 1);
		return CHAR;
	}
[ \t\n]+ ; /* ignore whitespace */
.	{
		yyerror("Invalid charactor in file\n");
		exit(-1);
	}

%%

void comment()
{
	char c;

	for(; ;) {
		while(( c = input()) != '*' &&
			c != EOF);

		unput(c);	
		if (c == '*') {
			while((c = input()) == '*') ;
			if (c == '/')
			break;
		}

		if (c == EOF) {
			yyerror("EOF in comment");
			exit(1);
		}
	}
}

void read_str()
{
	register char c;
	char * str = str_ptr;

	for (;;) {
		c = input();
		if (c == '"') {
			break;
		}
		if (c == EOF)
			yyerror("EOF found in string");
		if (c == '\n')
			yyerror("Unternimated string");
		if (c=='\\') {
			c = input();
			switch (c) {
				case 'n' :
					*str++ = '\n';
					break;
				case 't' :
					*str++ = '\t';
					break;
				case '\\' :
					*str++ = '\\';
					break;
				case '"' :
					*str++ = '"';
					break;
				case EOF :
					yyerror("EOF while scanning string");
					break;
				default :
					yyerror("Invalid escape char in string");
					break;
			}
		} else {
			*str++ = c;
		}
	}
	*str++ = '\0';
}

void yyerror(char *text)
{
	printf("yyerror = %s\n", text);
}

int yywrap(void) {
	return 1;
}

