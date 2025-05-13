(32) to (35): Arithmetic Expression Evaluation
LEX File: arith.l

%{
#include "y.tab.h"
#include <stdlib.h>
%}

%%

[0-9]+\.[0-9]+     { yylval = atof(yytext); return NUMBER; }
[0-9]+             { yylval = atof(yytext); return NUMBER; }
[ \t]              ;
[\n]               { return '\n'; }
.                  { return yytext[0]; }

%%
int yywrap() { return 1; }





▶️ Q(32)–Q(35): Evaluate Arithmetic Expressions
Input

markdown
Copy
Edit
0.33*12-4-4+(3*2)
Output

Copy
Edit
= 2.960000