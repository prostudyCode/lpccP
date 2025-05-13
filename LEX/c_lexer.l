 2. GENERAL LEX TEMPLATE for C Programming Language
📄 Filename: c_lexer.l




%{
#include <stdio.h>
%}

%%
"int"|"char"|"float"|"double"         { printf("Keyword: %s\n", yytext); }
"printf"                              { printf("Function: %s\n", yytext); }
"="                                   { printf("Assignment Operator: %s\n", yytext); }
[0-9]+\.[0-9]+                         { printf("Float Number: %s\n", yytext); }
[0-9]+                                { printf("Integer: %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]*                { printf("Identifier: %s\n", yytext); }
"(" | ")" | "{" | "}"                 { printf("Bracket: %s\n", yytext); }
";"                                   { printf("Semicolon: %s\n", yytext); }
","                                   { printf("Comma: %s\n", yytext); }
"\""([^\"\n]*)"\""                    { printf("String Literal: %s\n", yytext); }
"+"|"-"|"*"|"/"                        { printf("Operator: %s\n", yytext); }
[ \t\n]+                              ; // Ignore whitespace
.                                     { printf("Other Token: %s\n", yytext); }
%%

int main() {
    printf("Lexical Analysis of C Code:\n");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}




🧪 Example Test Input for C Code
{
int m=10,n=2,o;
o = m - n;
}


📤 Sample Output:

Bracket: {
Keyword: int
Identifier: m
Assignment Operator: =
Integer: 10
Comma: ,
Identifier: n
Assignment Operator: =
Integer: 2
Comma: ,
Identifier: o
Semicolon: ;
Identifier: o
Assignment Operator: =
Identifier: m
Operator: -
Identifier: n
Semicolon: ;
Bracket: }