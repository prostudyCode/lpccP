
(36): Variable Name Validation
LEX File: varname.l


%{
#include "y.tab.h"
%}

%%

[a-zA-Z_][a-zA-Z0-9_]*  { return VALID; }
[^a-zA-Z0-9_\n]+        { return INVALID; }
\n                      { return '\n'; }
[ \t]                   ;

%%
int yywrap() { return 1; }




Q(36): Variable Name Validation
Input
pUNE_2

Output
Valid variable name

Input
123abc

Output
Invalid variable name