#include <stdio.h>
#include <stdlib.h>

extern FILE *yyin;
extern int yy_flex_debug;
void yyparse();

int main(int argc, char **argv)
{
	if (argc == 2) {
		yyin = fopen(argv[1], "r");
		if (yyin == NULL) {
			fprintf(stderr, "Unable to open input file :%s\n", argv[1]);
		}
	}
	if (yyin == NULL) {
		printf("Using stdin as input\n");
		yyin = stdin;
	}
	yy_flex_debug = 1;
	yyparse();
	return 0;
}

void log(const char *fmt, ...)
{
}

