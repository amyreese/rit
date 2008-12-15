%{
/**** The beginnings of a lisp evaluator. ****/
#include <stdlib.h>
#include <stdio.h>
%}

%%

[a-z]   {
	   yylval.ti.value = 0.0;
	   yylval.ti.name =  (char *) strdup(yytext);
	   return VARIABLE;
        }

[0-9]+  {  
           yylval.ti.value = atof(yytext);
	   yylval.ti.name = NULL;
	   return NUMBER;
        }

\+    return PLUS;
\-    return MINUS;
\*    return TIMES;
\/    return DIVIDE;
\(    return LEFTPAREN;
\)    return RIGHTPAREN;

\n    return NEWLINE;

[ ]   ;

.       printf("Invalid character\n");

%%

int yywrap() {
  return 1;
}

