%{
/**** The beginnings of a calculator. ****/
#include <stdlib.h>
#include <stdio.h>
%}

%%

[a-z]   { yylval.ti.value = 0;
          yylval.ti.name =  (char *) strdup(yytext);
          return VARIABLE;
        }

[0-9]+  { yylval.ti.value = atoi(yytext);
          yylval.ti.name = NULL;
          return INTEGER;
        }

=       return ASSIGNMENT;
\+      return PLUS;
\-      return MINUS;
\*      return MULTIPLY;
\/      return DIVIDE;
\(      return LEFTPAREN;
\)      return RIGHTPAREN;
\n      return NEWLINE;
[ ]   ;
.       printf("Invalid character\n");

%%

int yywrap() {
 return 1;
}

