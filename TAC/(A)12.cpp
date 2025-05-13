(A)12.Write a program to generate three address code for the given simple expression.
INPUT
w = u*u - u*v+ v*v



#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Instruction {
    string result;
    string arg1;
    string op;
    string arg2;
};

int tempCount = 1;
string newTemp() {
    return "t" + to_string(tempCount++);
}

int main() {
    vector<Instruction> code;

    string t1 = newTemp();  // u * u
    code.push_back({t1, "u", "*", "u"});

    string t2 = newTemp();  // u * v
    code.push_back({t2, "u", "*", "v"});

    string t3 = newTemp();  // t1 - t2
    code.push_back({t3, t1, "-", t2});

    string t4 = newTemp();  // v * v
    code.push_back({t4, "v", "*", "v"});

    string t5 = newTemp();  // t3 + t4
    code.push_back({t5, t3, "+", t4});

    code.push_back({"w", t5, "=", ""});  // w = t5

    cout << "Three Address Code:\n";
    for (auto &inst : code) {
        if (inst.op == "=" && inst.arg2 == "")
            cout << inst.result << " = " << inst.arg1 << endl;
        else
            cout << inst.result << " = " << inst.arg1 << " " << inst.op << " " << inst.arg2 << endl;
    }

    return 0;
}
