%{
/**** The beginnings of a compiler. ****/
#include <stdlib.h>
#include <stdio.h>
%}

%%

if    return IF;
then  return THEN;
else  return ELSE;
for   return FOR;

[a-z]   {
	   yylval.ti.value = 0.0;
	   yylval.ti.code =  (char *) strdup(yytext);
	   return VARIABLE;
        }

[0-9]+  {  
           yylval.ti.value = atof(yytext);
	   yylval.ti.code = (char *) strdup(yytext);
	   return NUMBER;
        }

\+    return PLUS;
\-    return MINUS;
\*    return TIMES;
\/    return DIVIDE;
\=    return ASGN;
\<    return LT;
\>    return GT;
\<\=  return LE;
\>\=  return GE;
\=\=  return EQ;
\!\=  return NE;
\(    return LEFTPAREN;
\)    return RIGHTPAREN;
\{    return LEFTBRACE;
\}    return RIGHTBRACE;
\;    return SEMI;

\n    ;

[ ]   ;

.       printf("Invalid character\n");

%%

int yywrap() {
 return 1;
}

