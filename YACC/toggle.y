YACC File: toggle.y




%{
#include <stdio.h>
#include <ctype.h>
extern char str[100];
%}

%token STRING

%%

input:
    STRING '\n' {
        for(int j = 0; str[j]; j++) {
            if (islower(str[j]))
                str[j] = toupper(str[j]);
            else if (isupper(str[j]))
                str[j] = tolower(str[j]);
        }
        printf("Toggled: %s\n", str);
    }
;

%%

int main() {
    printf("Enter a string:\n");
    return yyparse();
}

int yyerror(char *msg) {
    printf("Error: %s\n", msg);
    return 0;
}
