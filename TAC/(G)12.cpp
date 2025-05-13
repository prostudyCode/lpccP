(G)12.Write a program to generate three address code for the given simple expression.
INPUT
a = f ^ r – u * f * t – p


#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Instruction {
    string result, arg1, op, arg2;
};

int tempCount = 1;
string newTemp() {
    return "t" + to_string(tempCount++);
}

int main() {
    vector<Instruction> code;

    string t1 = newTemp();  // f ^ r
    code.push_back({t1, "f", "^", "r"});

    string t2 = newTemp();  // u * f
    code.push_back({t2, "u", "*", "f"});

    string t3 = newTemp();  // t2 * t
    code.push_back({t3, t2, "*", "t"});

    string t4 = newTemp();  // t1 - t3
    code.push_back({t4, t1, "-", t3});

    string t5 = newTemp();  // t4 - p
    code.push_back({t5, t4, "-", "p"});

    code.push_back({"a", t5, "=", ""});

    cout << "Three Address Code:\n";
    for (auto &inst : code) {
        if (inst.op == "=")
            cout << inst.result << " = " << inst.arg1 << endl;
        else
            cout << inst.result << " = " << inst.arg1 << " " << inst.op << " " << inst.arg2 << endl;
    }

    return 0;
}
