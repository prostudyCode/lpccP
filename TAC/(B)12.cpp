(B)12.Write a program to generate three address code for the given simple expression.
INPUT
y=x*x + w-v / r+r


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

    string t1 = newTemp();  // x * x
    code.push_back({t1, "x", "*", "x"});

    string t2 = newTemp();  // v / r
    code.push_back({t2, "v", "/", "r"});

    string t3 = newTemp();  // t1 + w
    code.push_back({t3, t1, "+", "w"});

    string t4 = newTemp();  // t3 - t2
    code.push_back({t4, t3, "-", t2});

    string t5 = newTemp();  // t4 + r
    code.push_back({t5, t4, "+", "r"});

    code.push_back({"y", t5, "=", ""});

    cout << "Three Address Code:\n";
    for (auto &inst : code) {
        if (inst.op == "=")
            cout << inst.result << " = " << inst.arg1 << endl;
        else
            cout << inst.result << " = " << inst.arg1 << " " << inst.op << " " << inst.arg2 << endl;
    }

    return 0;
}
