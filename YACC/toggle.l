 (37): Toggle Case Using YACC
LEX File: toggle.l


%{
#include "y.tab.h"
char str[100];
int i = 0;
%}

%%

[a-zA-Z]+  { strcpy(str, yytext); return STRING; }
\n         { return '\n'; }
[ \t]      ;

%%
int yywrap() { return 1; }




 Q(37): Toggle Case of String
Input
Pune

Output
Toggled: pUNE

Input
pUNE

Output
Toggled: Pune