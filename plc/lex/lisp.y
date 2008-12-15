%{
#define YYDEBUG 1
#include "lisp.h"
%}
%union {
  tokenInfo ti;
}

%token PLUS MINUS TIMES DIVIDE LEFTPAREN RIGHTPAREN NEWLINE
%token <ti> VARIABLE
%token <ti> NUMBER
%type <ti> expr

%%

program: program statement
         | /* EMPTY */
       ;

statement: expr NEWLINE 
	     { printf("%g\n", $1.value); }
         ;

expr: NUMBER            { $$ = $1; }
    ;

%%
#include "lisp.yy.c"
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
