(A)4.Write a program to generate Intermediate code of a two-pass Assembler for the given Assembly language source code.



#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <sstream>
using namespace std;

struct Symbol {
    string name;
    int address;
};

map<string, string> registers = {
    {"AREG", "1"},
    {"BREG", "2"},
    {"CREG", "3"},
    {"DREG", "4"}
};

map<string, pair<string, string>> opcodes = {
    {"START", {"AD", "01"}},
    {"END",   {"AD", "02"}},
    {"READ",  {"IS", "09"}},
    {"MOVER", {"IS", "04"}},
    {"SUB",   {"IS", "05"}},
    {"STOP",  {"IS", "00"}},
    {"DS",    {"DL", "01"}}
};

int main() {
    vector<string> code = {
        "START 100",
        "READ A",
        "READ B",
        "MOVER AREG, A",
        "SUB AREG, B",
        "STOP",
        "A DS 1",
        "B DS 1",
        "END"
    };

    map<string, int> symbolTable;
    int LC = 0;
    int symIndex = 1;

    // Pass 1: Build Symbol Table
    for (const string& line : code) {
        stringstream ss(line);
        vector<string> tokens;
        string tok;
        while (ss >> tok) tokens.push_back(tok);

        if (tokens.empty()) continue;

        if (tokens[0] == "START") {
            LC = stoi(tokens[1]);
        } else if (tokens[0] == "DS") {
            // Do nothing here
        } else if (tokens.size() == 3 && tokens[1] == "DS") {
            symbolTable[tokens[0]] = LC;
            LC += stoi(tokens[2]);
        } else if (tokens[0] == "END") {
            // Nothing
        } else {
            if (tokens.size() == 2 && tokens[0] == "READ") {
                symbolTable[tokens[1]] = -1;
            } else if (tokens.size() == 3) {
                string operand = tokens[2];
                if (operand.back() == ',') operand.pop_back();
                if (symbolTable.find(operand) == symbolTable.end()) {
                    symbolTable[operand] = -1;
                }
            }
            LC++;
        }
    }

    // Reset LC for Pass 2
    LC = 0;
    cout << "Intermediate Code:\n";

    for (const string& line : code) {
        stringstream ss(line);
        vector<string> tokens;
        string tok;
        while (ss >> tok) tokens.push_back(tok);

        if (tokens.empty()) continue;

        string mnemonic = tokens[0];

        if (mnemonic == "START") {
            LC = stoi(tokens[1]);
            cout << "(" << opcodes[mnemonic].first << "," << opcodes[mnemonic].second << ") " << "(C," << LC << ")\n";
        } else if (mnemonic == "END") {
            cout << "(" << opcodes[mnemonic].first << "," << opcodes[mnemonic].second << ")\n";
        } else if (tokens.size() == 3 && tokens[1] == "DS") {
            string label = tokens[0];
            int size = stoi(tokens[2]);
            symbolTable[label] = LC;
            cout << "(" << opcodes["DS"].first << "," << opcodes["DS"].second << ") " << "(C," << size << ")\n";
            LC += size;
        } else if (mnemonic == "READ" || mnemonic == "STOP") {
            cout << "(" << opcodes[mnemonic].first << "," << opcodes[mnemonic].second << ") ";
            if (mnemonic == "READ") {
                cout << "(S," << tokens[1] << ")";
            }
            cout << "\n";
            LC++;
        } else {
            // IS instructions like MOVER, SUB
            string reg = registers[tokens[1]];
            string operand = tokens[2];
            if (operand.back() == ',') operand.pop_back();
            cout << "(" << opcodes[mnemonic].first << "," << opcodes[mnemonic].second << ") ";
            cout << "(" << reg << ") ";
            cout << "(S," << operand << ")\n";
            LC++;
        }
    }

    return 0;
}

