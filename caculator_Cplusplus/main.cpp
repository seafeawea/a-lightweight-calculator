//
//  main.cpp
//  caculator_Cplusplus
//
//  Created by XZ on 15/12/3.
//  Copyright © 2015年 XZ. All rights reserved.
//

#include <iostream>
#include <string>
#include "caculator.hpp"
using namespace std;
//using namespace caculator;



int main(int argc, const char* argv[])
{
    string expr;
    int answer;
    cout << "Please enter an expression to evaluate(only include operator +-*/ and bracket())\r\n";
    cout << "Press q to exit\r\n";
    cout << ">>> ";

    while (getline(cin, expr)) {
        if (expr == "q") break;
        try {
            answer = evaluate(expr);
            cout << "Result: " << answer << endl;
        } catch (caculator_error& e) {
            cout << "Error: " << e._message << endl;
        }
        cout << ">>> ";
    }
    return 0;
}
