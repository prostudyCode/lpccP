(F)12.Write a program to generate three address code for the given simple expression.
INPUT
a = m * n - o – p / q


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

    string t1 = newTemp();  // m * n
    code.push_back({t1, "m", "*", "n"});

    string t2 = newTemp();  // t1 - o
    code.push_back({t2, t1, "-", "o"});

    string t3 = newTemp();  // p / q
    code.push_back({t3, "p", "/", "q"});

    string t4 = newTemp();  // t2 - t3
    code.push_back({t4, t2, "-", t3});

    code.push_back({"a", t4, "=", ""});

    cout << "Three Address Code:\n";
    for (auto &inst : code) {
        if (inst.op == "=")
            cout << inst.result << " = " << inst.arg1 << endl;
        else
            cout << inst.result << " = " << inst.arg1 << " " << inst.op << " " << inst.arg2 << endl;
    }

    return 0;
}
