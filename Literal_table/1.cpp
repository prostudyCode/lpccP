(A)2. Write a program to generate Literal table of a two-pass Assembler for the given Assembly language source code.


#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <sstream>
using namespace std;

struct Literal {
    string name;
    int address;
};

bool isLiteral(const string& operand) {
    return operand.size() >= 2 && operand[0] == '=' && operand[1] == '\'';
}

int main() {
    vector<string> code = {
        "START 100",
        "READ A",
        "READ B",
        "MOVER AREG, ='50'",
        "MOVER BREG, ='60'",
        "ADD AREG, BREG",
        "LOOP MOVER CREG, A",
        "     ADD CREG, ='10'",
        "COMP CREG, B",
        "     BC LT, LOOP",
        "NEXT SUB AREG, ='10'",
        "COMP AREG, B",
        "BC GT, NEXT",
        "STOP",
        "A DS 1",
        "B DS 1",
        "END"
    };

    int LC = 0;
    bool started = false;

    map<string, int> literalTable;
    vector<string> literalPool;

    for (const string& line : code) {
        stringstream ss(line);
        vector<string> tokens;
        string token;
        while (ss >> token) {
            tokens.push_back(token);
        }

        if (tokens.empty()) continue;

        // Handle START
        if (tokens[0] == "START") {
            LC = stoi(tokens[1]);
            started = true;
            continue;
        }

        if (!started) continue;

        // Collect literals from operands
        for (const string& tok : tokens) {
            if (isLiteral(tok) && literalTable.find(tok) == literalTable.end()) {
                literalPool.push_back(tok);
                literalTable[tok] = -1;  // placeholder for address
            }
        }

        // After END, assign addresses to literals
        if (tokens[0] == "END") {
            for (const string& lit : literalPool) {
                if (literalTable[lit] == -1) {
                    literalTable[lit] = LC++;
                }
            }
        } else {
            LC++;  // Each instruction = 1 memory word
        }
    }

    // Print Literal Table
    cout << "Literal Table:\n";
    cout << left << setw(10) << "Literal" << "Address\n";
    for (const auto& entry : literalTable) {
        cout << left << setw(10) << entry.first << entry.second << "\n";
    }

    return 0;
}

