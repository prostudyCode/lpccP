YACC File: builtin.y


%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
%}

%token NUMBER LENGTH
%token SQRT STRLEN SIN COS POW LOG

%left '+' '-'
%left '*' '/'
%right UMINUS

%%

input:
    | input line
;

line:
    expr '\n' { printf("= %f\n", $1); }
;

expr:
    expr '+' expr     { $$ = $1 + $3; }
  | expr '-' expr     { $$ = $1 - $3; }
  | expr '*' expr     { $$ = $1 * $3; }
  | expr '/' expr     { $$ = $1 / $3; }
  | '-' expr %prec UMINUS { $$ = -$2; }
  | '(' expr ')'      { $$ = $2; }
  | SQRT '(' expr ')'     { $$ = sqrt($3); }
  | STRLEN '(' LENGTH ')' { $$ = $3; }
  | SIN '(' expr ')'      { $$ = sin($3); }
  | COS '(' expr ')'      { $$ = cos($3); }
  | LOG '(' expr ')'      { $$ = log($3); }
  | POW '(' expr ',' expr ')' { $$ = pow($3, $5); }
  | NUMBER
;

%%

int main() {
    printf("Enter expression:\n");
    return yyparse();
}

int yyerror(char *s) {
    fprintf(stderr, "Error: %s\n", s);
    return 0;
}
