(A)6.Write a program to generate MDT(Macro Definition Table) of a two-pass Macro processor.



#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <iomanip>

using namespace std;

struct MacroDefinition {
    string name;
    vector<string> parameters;
    vector<string> body;
};

string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

vector<string> split(const string& s) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (tokenStream >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

void generateMDT(const vector<string>& input) {
    map<string, MacroDefinition> macroTable;
    vector<pair<string, vector<string>>> mdtEntries;
    
    for (size_t i = 0; i < input.size(); i++) {
        string line = input[i];
        vector<string> tokens = split(trim(line));
        
        if (tokens.empty()) continue;
        
        if (tokens[0] == "MACRO") {
            MacroDefinition macro;
            macro.name = tokens[1];
            
            // Store parameters
            for (size_t j = 2; j < tokens.size(); j++) {
                macro.parameters.push_back(tokens[j]);
            }
            
            // Process macro body
            i++;
            while (i < input.size() && trim(input[i]) != "MEND") {
                string bodyLine = input[i];
                // Replace parameters with placeholders (#1, #2, etc.)
                for (size_t paramIdx = 0; paramIdx < macro.parameters.size(); paramIdx++) {
                    string param = macro.parameters[paramIdx];
                    size_t pos = bodyLine.find(param);
                    while (pos != string::npos) {
                        bodyLine.replace(pos, param.length(), "#" + to_string(paramIdx+1));
                        pos = bodyLine.find(param, pos + 2);
                    }
                }
                macro.body.push_back(bodyLine);
                i++;
            }
            macro.body.push_back("MEND");
            macroTable[macro.name] = macro;
            
            // Add to MDT entries
            for (const auto& line : macro.body) {
                mdtEntries.emplace_back(macro.name, vector<string>{line});
            }
        }
    }
    
    // Print MDT in the requested format
    cout << "Macro Definition Table (MDT):" << endl;
    cout << "Index\tLine" << endl;
    int index = 0;
    for (const auto& entry : mdtEntries) {
        cout << index << "\t" << entry.second[0] << endl;
        index++;
    }
}

int main() {
    vector<string> input = {
        "LOAD A",
        "STORE B",
        "MACRO ABC",
        "LOAD p",
        "SUB q",
        "MEND",
        "MACRO ADD1 ARG",
        "LOAD X",
        "STORE ARG",
        "MEND",
        "",
        "MACRO ADD5 A1, A2, A3",
        "STORE A2",
        "ADD1 5",
        "ADD1 10",
        "LOAD A1",
        "LOAD A3",
        "MEND",
        "ABC",
        "ADD5 D1, D2, D3",
        "END"
    };
    
    generateMDT(input);
    
    return 0;
}

