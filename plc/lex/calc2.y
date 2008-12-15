%{
#define YYDEBUG 1
#include "calc2.h"
%}
%union {
  tokenInfo ti;
}

%token ASSIGNMENT PLUS MINUS MULTIPLY DIVIDE NEWLINE LEFTPAREN RIGHTPAREN
%token <ti> VARIABLE 
%token <ti> INTEGER 
%type <ti> expr
%type <ti> term
%type <ti> sum
%type <ti> product

%%

program: program statement
       | 
       ;

statement: expr NEWLINE 
	     { printf("%g\n", $1.value); }
         | VARIABLE ASSIGNMENT expr NEWLINE
           { putVar($1.name, $3.value); }
         ;

expr:	sum { $$ = $1; };

term:	INTEGER		{ $$ = $1; }
		| VARIABLE	{ if (getVar($1.name) != 0) {
										varRec *tmp = getVar($1.name);
										$$.value = tmp -> value;
									}
								};

sum:	sum PLUS product			{ $$.value = $1.value + $3.value; }
		| sum MINUS product			{ $$.value = $1.value - $3.value; }
		|	LEFTPAREN sum RIGHTPAREN	{ $$ = $2; }
		|	product								{ $$ = $1; };

product:	product MULTIPLY term	{ $$.value = $1.value * $3.value; }
				| product term					{ $$.value = $1.value * $2.value; }
				| product DIVIDE term		{ $$.value = $1.value / $3.value; }
				|	LEFTPAREN sum RIGHTPAREN	{ $$ = $2; }
				| term								{ $$ = $1; };


%%
#include "calc2.yy.c"
int yyerror(char *s, int lineNumber) {
  fprintf(stderr, "Error: %s at line number %d\n", s, lineNumber);
  clearVar();
  return 0;
}

int main() {
  yydebug = 0;
  yyparse();
  clearVar();
  return 0;
}
