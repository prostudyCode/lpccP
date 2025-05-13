To run the LEX program on Ubuntu, follow these steps:

Step-by-Step Guide:
1. Install Required Packages
First, make sure you have flex (the LEX implementation) and gcc installed:

bash
sudo apt update
sudo apt install flex gcc

2. Save the LEX Program
Create a file called c_lexer.l and paste the LEX code provided earlier:

bash
nano c_lexer.l
(Paste the code, then press Ctrl+O to save, Enter to confirm, and Ctrl+X to exit)

3. Create Input File
Create a file called input.c with your C code:

bash
nano input.c
(Paste your input code, then save and exit)

4. Generate Lexical Analyzer
Run these commands to compile and build the analyzer:

bash
flex c_lexer.l
gcc lex.yy.c -o c_lexer -ll

5. Run the Analyzer
Execute the program with your input file:

bash
./c_lexer < input.c