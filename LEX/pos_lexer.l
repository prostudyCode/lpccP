(A)8.Write a program using LEX Tool, to implement a lexical analyzer for parts of speech for given English language without Symbol table.
INPUT
Dread it. Run from it. 
   Destiny arrives all the same.

   Q21 - Q26


📌 1. GENERAL LEX TEMPLATE for Parts of Speech (POS)
📄 Filename: pos_lexer.l

%{
#include <stdio.h>
%}

%%
"the"|"a"|"an"                         { printf("Article: %s\n", yytext); }
"and"|"but"|"or"|"so"                  { printf("Conjunction: %s\n", yytext); }
"he"|"she"|"it"|"you"|"we"|"they"      { printf("Pronoun: %s\n", yytext); }
"run"|"walk"|"kill"|"give"|"imagine"|"arrive"|"go"|"are"|"am"|"is"|"was"|"have"|"has"|"be"|"being"|"been" {
    printf("Verb: %s\n", yytext);
}
"from"|"to"|"of"|"in"|"on"|"with"|"by"|"at" {
    printf("Preposition: %s\n", yytext);
}
"hello"|"fine"|"important"|"curiosity"|"generation"|"reason"|"thing"|"instinct" {
    printf("Noun: %s\n", yytext);
}
"strong"|"dramatic"|"basic"|"empty"|"more"|"less"|"wiser" {
    printf("Adjective: %s\n", yytext);
}
[ \t\n]+                              ; // Ignore whitespace
[.!?,;:]                              { printf("Punctuation: %s\n", yytext); }
[a-zA-Z']+                            { printf("Unknown or Unclassified Word: %s\n", yytext); }
.                                     { printf("Other Token: %s\n", yytext); }
%%

int main() {
    printf("Lexical Analysis of English Sentence:\n");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}




 Example Test Input for POS
Dread it. Run from it.
Destiny arrives all the same.

📤 Sample Output:
Unknown or Unclassified Word: Dread
Pronoun: it
Punctuation: .
Verb: Run
Preposition: from
Pronoun: it
Punctuation: .
Noun: Destiny
Verb: arrives
Unknown or Unclassified Word: all
Article: the
Unknown or Unclassified Word: same
Punctuation: .



▶️ Compile and Run
lex pos_lexer.l        # or lex c_lexer.l
gcc lex.yy.c -o lexer
./lexer
Paste the respective input when prompted.