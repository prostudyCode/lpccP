(B)7.Write a program to generate MNT(Macro Name Table) of a two-pass Macro processor.

#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <iomanip>

using namespace std;

struct MacroDefinition {
    string name;
    int mdtIndex;
};

void generateMNT(const vector<string>& input) {
    vector<MacroDefinition> mnt;
    int mdtIndex = 0;
    bool inMacro = false;

    cout << "Macro Name Table (MNT):" << endl;
    cout << "Macro\tMDT Index" << endl;
    cout << "----------------" << endl;

    for (const auto& line : input) {
        string trimmed = line;
        // Simple trim (remove leading/trailing whitespace)
        trimmed.erase(0, trimmed.find_first_not_of(" \t"));
        trimmed.erase(trimmed.find_last_not_of(" \t") + 1);

        if (trimmed.empty()) continue;

        vector<string> tokens;
        istringstream iss(trimmed);
        string token;
        while (iss >> token) {
            tokens.push_back(token);
        }

        if (tokens.empty()) continue;

        if (tokens[0] == "MACRO") {
            if (tokens.size() > 1) {
                string macroName = tokens[1];
                // Handle macros with parameters (take just the name)
                size_t commaPos = macroName.find(',');
                if (commaPos != string::npos) {
                    macroName = macroName.substr(0, commaPos);
                }
                mnt.push_back({macroName, mdtIndex});
                inMacro = true;
            }
        }
        else if (tokens[0] == "MEND") {
            inMacro = false;
            mdtIndex++; // MEND counts as one entry
        }
        else if (inMacro) {
            mdtIndex++;
        }
    }

    // Print MNT in the requested format
    for (const auto& entry : mnt) {
        cout << entry.name << "\t" << entry.mdtIndex << endl;
    }
}

int main() {
    vector<string> input = {
        "LOAD J",
        "STORE M",
        "MACRO EST1",
        "LOAD e",
        "ADD d",
        "MEND",
        "MACRO EST ABC",
        "EST1",
        "STORE ABC",
        "MEND",
        "MACRO ADD7 P4, P5, P6",
        "LOAD P5",
        "EST 8",
        "SUB4 2",
        "STORE P4",
        "STORE P6",
        "MEND",
        "EST",
        "ADD7 C4, C5, C6",
        "END"
    };

    generateMNT(input);

    return 0;
}
