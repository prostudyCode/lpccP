YACC File: varname.y

%{
#include <stdio.h>
%}

%token VALID INVALID

%%

start:
    VALID '\n'  { printf("Valid variable name\n"); }
  | INVALID '\n' { printf("Invalid variable name\n"); }
;

%%

int main() {
    printf("Enter a variable name:\n");
    return yyparse();
}

int yyerror(char *s) {
    printf("Error: %s\n", s);
    return 0;
}
