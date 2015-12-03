//
//  caculator.h
//  caculator_Cplusplus
//
//  Created by XZ on 15/12/3.
//  Copyright © 2015年 XZ. All rights reserved.
//

#ifndef caculator_h
#define caculator_h

#include<iostream>
#include<stdexcept>
#include<string>
#include<stack>

using namespace std;

//namespace caculator {
    
class caculator_error : runtime_error {

public:
    caculator_error(const string& expr, const string& message) : runtime_error(message), _expr(expr),_message(message)
    {}
#if __cplusplus >= 201103L
    ~caculator_error() { }
#else
    ~caculator_error() throw() { }
#endif

    string _expr;
    string _message;
};
    
enum
{
    OPERATOR_NULL,
    OPERATOR_ADDITION,       /// +
    OPERATOR_SUBTRACTION,    /// -
    OPERATOR_MULTIPLICATION, /// *
    OPERATOR_DIVISION,       /// /
    //OPERATOR_MODULO,         /// %
};

struct Operator {
    Operator(int opr, int leftValu, int pre): op(opr), leftVal(leftValu), precedence(pre){}
    int op;
    int leftVal;
    int precedence;
};

class ExpressionParser {
public:
    int eval(const string &expr);
    ExpressionParser(){};
    ~ExpressionParser(){};
    
private:
    char getCharacter();
    void eatSpace();
    bool isEnd();
    int caculate(Operator op, int v1, int v2);
    int parseVal();
    int parseDecimal();
    int checkZero(int value);
    Operator parseOp();
    int parseExpr();
    
private:
    string _expr;
    int _index;
    stack<Operator> _stack;

};

int evaluate(const string& expr) {
    ExpressionParser parser;
    return parser.eval(expr);
    //return 1;
}

//}

#endif /* caculator_h */
