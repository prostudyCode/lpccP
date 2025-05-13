(A)3.Write a program to generate Pool table of a two-pass Assembler for the given Assembly language source code.


#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

bool isLiteral(const string& token) {
    return token.size() >= 3 && token[0] == '=' && token[1] == '\'';
}

int main() {
    vector<string> code = {
        "START 100",
        "READ A",
        "MOVER AREG, ='1'",
        "MOVEM AREG, B",
        "MOVER BREG, ='6'",
        "ADD AREG, BREG",
        "COMP AREG, A",
        "BC GT, LAST",
        "LTORG",
        "NEXT SUB AREG, ='1'",
        "MOVER CREG, B",
        "ADD CREG, ='8'",
        "MOVEM CREG, B",
        "PRINT B",
        "LAST STOP",
        "A DS 1",
        "B DS 1",
        "END"
    };

    int LC = 0;
    bool started = false;

    vector<string> literalList;
    map<string, int> literalTable;
    vector<int> poolTable;

    int literalIndex = 0;

    for (size_t i = 0; i < code.size(); ++i) {
        stringstream ss(code[i]);
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

        // If END or LTORG -> assign addresses to pending literals
        if (tokens[0] == "LTORG" || tokens[0] == "END") {
            poolTable.push_back(literalIndex + 1);  // Pool starts from index+1 (1-based)
            for (const string& lit : literalList) {
                if (literalTable[lit] == -1) {
                    literalTable[lit] = LC++;
                    literalIndex++;
                }
            }
            literalList.clear();
            if (tokens[0] == "END") break;
            continue;
        }

        // Scan for literals
        for (const string& tok : tokens) {
            if (isLiteral(tok) && literalTable.find(tok) == literalTable.end()) {
                literalList.push_back(tok);
                literalTable[tok] = -1;  // placeholder
            }
        }

        LC++;  // each instruction is 1 word
    }

    // --- OUTPUT ---
    // Literal Table
    cout << "Literal Table:\n";
    cout << left << setw(10) << "Literal" << "Address\n";
    for (const auto& entry : literalTable) {
        cout << left << setw(10) << entry.first << entry.second << "\n";
    }

    // Pool Table
    cout << "\nPool Table:\n";
    cout << "Pool#\tIndex (1-based in literal table)\n";
    for (size_t i = 0; i < poolTable.size(); ++i) {
        cout << i + 1 << "\t" << poolTable[i] << "\n";
    }

    return 0;
}

