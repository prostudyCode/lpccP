/* (E)12. Write a program to generate three address code for the given simple expression.
INPUT
t = j / k – y / u - i
*/



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

    string t1 = newTemp();  // j / k
    code.push_back({t1, "j", "/", "k"});

    string t2 = newTemp();  // y / u
    code.push_back({t2, "y", "/", "u"});

    string t3 = newTemp();  // t1 - t2
    code.push_back({t3, t1, "-", t2});

    string t4 = newTemp();  // t3 - i
    code.push_back({t4, t3, "-", "i"});

    code.push_back({"t", t4, "=", ""});

    cout << "Three Address Code:\n";
    for (auto &inst : code) {
        if (inst.op == "=")
            cout << inst.result << " = " << inst.arg1 << endl;
        else
            cout << inst.result << " = " << inst.arg1 << " " << inst.op << " " << inst.arg2 << endl;
    }

    return 0;
}
