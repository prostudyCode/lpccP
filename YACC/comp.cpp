🛠️ Compilation Steps for All
Save the .l and .y files.

Run:

bash

yacc -d file.y
lex file.l
gcc lex.yy.c y.tab.c -lm -o output
./output