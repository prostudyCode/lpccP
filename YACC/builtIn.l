 (38), (39), (40): Built-in Functions (math, string)
LEX File: builtin.l


%{
#include "y.tab.h"
#include <string.h>
%}

%%

"sqrt"      { return SQRT; }
"strlen"    { return STRLEN; }
"sin"       { return SIN; }
"cos"       { return COS; }
"pow"       { return POW; }
"log"       { return LOG; }

[0-9]+      { yylval = atof(yytext); return NUMBER; }
\"[a-zA-Z]+\" { yylval = strlen(yytext) - 2; return LENGTH; }

"("         { return '('; }
")"         { return ')'; }
","         { return ','; }
[ \t\n]     ;
.           { return yytext[0]; }

%%
int yywrap() { return 1; }




Q(38): Built-in Function: sqrt(36) and strlen("pune")
Input
sqrt(36)

Output
= 6.000000

Input
strlen("pune")

Output
= 4.000000