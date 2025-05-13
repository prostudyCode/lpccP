
(A)5.Write a program to generate Intermediate code of a two-pass Macro processor.


#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>

using namespace std;

// Structure to represent a macro definition
struct MacroDefinition {
    string name;
    vector<string> parameters;
    vector<string> body;
};

// Function to trim whitespace from a string
string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

// Function to split a string into tokens
vector<string> split(const string& s) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (tokenStream >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to process the input and generate intermediate code
void generateIntermediateCode(const vector<string>& input) {
    map<string, MacroDefinition> macroTable;
    vector<string> intermediateCode;
    vector<string> expandedCode;
    
    // Pass 1: Process macro definitions
    for (size_t i = 0; i < input.size(); i++) {
        string line = input[i];
        vector<string> tokens = split(trim(line));
        
        if (tokens.empty()) continue;
        
        if (tokens[0] == "MACRO") {
            MacroDefinition macro;
            macro.name = tokens[1];
            
            // Extract parameters if any
            for (size_t j = 2; j < tokens.size(); j++) {
                macro.parameters.push_back(tokens[j]);
            }
            
            // Collect macro body until MEND
            i++; // Move to next line
            while (i < input.size() && trim(input[i]) != "MEND") {
                macro.body.push_back(input[i]);
                i++;
            }
            
            // Add macro to macro table
            macroTable[macro.name] = macro;
        } else {
            intermediateCode.push_back(line);
        }
    }
    
    // Pass 2: Expand macro calls
    for (const string& line : intermediateCode) {
        vector<string> tokens = split(trim(line));
        
        if (tokens.empty()) {
            expandedCode.push_back("");
            continue;
        }
        
        // Check if this is a macro call
        if (macroTable.find(tokens[0]) != macroTable.end()) {
            MacroDefinition macro = macroTable[tokens[0]];
            vector<string> args;
            
            // Extract arguments if any
            for (size_t i = 1; i < tokens.size(); i++) {
                args.push_back(tokens[i]);
            }
            
            // Expand macro body with argument substitution
            for (const string& macroLine : macro.body) {
                string expandedLine = macroLine;
                
                // Replace parameters with arguments
                for (size_t i = 0; i < macro.parameters.size() && i < args.size(); i++) {
                    string param = macro.parameters[i];
                    string arg = args[i];
                    
                    size_t pos = expandedLine.find(param);
                    while (pos != string::npos) {
                        expandedLine.replace(pos, param.length(), arg);
                        pos = expandedLine.find(param, pos + arg.length());
                    }
                }
                
                expandedCode.push_back(expandedLine);
            }
        } else {
            expandedCode.push_back(line);
        }
    }
    
    // Output the intermediate code
    cout << "Intermediate Code (Expanded):" << endl;
    cout << "---------------------------" << endl;
    for (const string& line : expandedCode) {
        if (trim(line) == "MEND" || trim(line) == "MACRO") continue;
        cout << line << endl;
    }
}

int main() {
    // Input program
    vector<string> input = {
        "LOAD A",
        "MACRO ABC",
        "LOAD p",
        "SUB q",
        "MEND",
        "STORE B",
        "MULT D",
        "MACRO ADD1 ARG",
        "LOAD X",
        "STORE ARG",
        "MEND",
        "",
        "LOAD B",
        "MACRO ADD5 A1, A2, A3",
        "STORE A2",
        "ADD1 5",
        "ADD1 10",
        "LOAD A1",
        "LOAD A3",
        "MEND",
        "ADD1 t",
        "ABC",
        "ADD5 D1, D2, D3",
        "END"
    };
    
    generateIntermediateCode(input);
    
    return 0;
}
