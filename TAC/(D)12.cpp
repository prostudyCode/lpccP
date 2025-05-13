(D)12.Write a program to generate three address code for the given simple expression.
INPUT
t = o*a - o*b+ o*c


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

    string t1 = newTemp();  // o * a
    code.push_back({t1, "o", "*", "a"});

    string t2 = newTemp();  // o * b
    code.push_back({t2, "o", "*", "b"});

    string t3 = newTemp();  // t1 - t2
    code.push_back({t3, t1, "-", t2});

    string t4 = newTemp();  // o * c
    code.push_back({t4, "o", "*", "c"});

    string t5 = newTemp();  // t3 + t4
    code.push_back({t5, t3, "+", t4});

    code.push_back({"t", t5, "=", ""});

    cout << "Three Address Code:\n";
    for (auto &inst : code) {
        if (inst.op == "=")
            cout << inst.result << " = " << inst.arg1 << endl;
        else
            cout << inst.result << " = " << inst.arg1 << " " << inst.op << " " << inst.arg2 << endl;
    }

    return 0;
}
