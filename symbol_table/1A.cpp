(A)1. Write a program to generate Symbol table of a two-pass Assembler for the given Assembly language source code. 

#include <iostream>
#include <iomanip>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

struct Symbol {
    string label;
    int address;
};

bool isInstruction(const string& word) {
    // Instructions and directives that shouldn't be in symbol table
    vector<string> instructions = {
        "START", "READ", "MOVER", "COMP", "BC", "SUB", "STOP", "END"
    };
    for (const string& inst : instructions) {
        if (word == inst) return true;
    }
    return false;
}

int main() {
    vector<string> code = {
        "START 100",
        "READ A",
        "READ B",
        "LOOP MOVER AREG, A",
        "      MOVER BREG, B",
        "      COMP BREG, ='2'",
        "      BC GT, LOOP",
        "BACK SUB AREG, B",
        "      COMP AREG, ='5'",
        "      BC LT, BACK",
        "      STOP",
        "A DS 1",
        "B DS 1",
        "END"
    };

    map<string, int> symbolTable;
    int LC = 0;
    bool started = false;

    for (const string& line : code) {
        stringstream ss(line);
        vector<string> tokens;
        string token;
        while (ss >> token) {
            tokens.push_back(token);
        }

        if (tokens.empty()) continue;

        // START
        if (tokens[0] == "START") {
            LC = stoi(tokens[1]);
            started = true;
            continue;
        }

        if (!started) continue;

        // END
        if (tokens[0] == "END") break;

        // DS declaration
        if (tokens.size() >= 3 && tokens[1] == "DS") {
            symbolTable[tokens[0]] = LC;
            LC += stoi(tokens[2]);
            continue;
        }

        // Label line (LOOP, BACK, etc.)
        if (tokens.size() >= 2 && !isInstruction(tokens[0])) {
            // First token is a label
            symbolTable[tokens[0]] = LC;
        }

        LC++;  // Increment LC for each instruction
    }

    // Print Symbol Table
    cout << "Symbol Table:\n";
    cout << left << setw(10) << "Label" << "Address\n";
    for (const auto& entry : symbolTable) {
        cout << left << setw(10) << entry.first << entry.second << "\n";
    }

    return 0;
}

