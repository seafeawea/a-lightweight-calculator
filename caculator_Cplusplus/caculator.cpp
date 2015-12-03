//
//  caculator.cpp
//  caculator_Cplusplus
//
//  Created by XZ on 15/12/3.
//  Copyright © 2015年 XZ. All rights reserved.
//

#include "caculator.hpp"
using namespace std;


int ExpressionParser::eval(const string& expr) {
    int result = 0;
    _index = 0;
    _expr = expr;
    try {
        result = parseExpr();
    } catch (caculator_error & e) {
        while(!_stack.empty())
            _stack.pop();
        throw;
    }
    return result;
}

int ExpressionParser::parseExpr() {
    _stack.push(Operator(OPERATOR_NULL, 0, 0));
    eatSpace();
    int value = parseVal();
    
    while (!_stack.empty()) {
        Operator op = parseOp();
        while (op.precedence <= _stack.top().precedence) {
            if (_stack.top().op == OPERATOR_NULL) {
                _stack.pop();
                return value;
            }
            value = caculate(_stack.top(), _stack.top().leftVal, value);
            _stack.pop();
        }
        op.leftVal = value;
        _stack.push(op);
        value = parseVal();
    }
    return 0;
}

int ExpressionParser::parseVal() {
    int result;
    eatSpace();
    char currentChar = getCharacter();
    if (currentChar >= '0' && currentChar <= '9') {
        result = parseDecimal();
        return result;
    }
    switch (currentChar) {
        case '(':
            _index++;
            result = parseExpr();
            eatSpace();
            if (getCharacter() != ')') {
                throw caculator_error(_expr, "syntax ')' exceped at expression");
            }
            _index++;
            return result;
            break;
            
        default:
            throw caculator_error(_expr, "unexceped format");
            break;
    }
}

int ExpressionParser::parseDecimal() {
    int result;
    char c;
    result = getCharacter() - '0';
    _index++;
    c = getCharacter();
    while (c >= '0' && c <= '9') {
        result = result*10 + c-'0';
        _index++;
        c = getCharacter();
    }
    return result;
}

Operator ExpressionParser::parseOp() {
    char c = getCharacter();
    switch (c) {
        case '+': _index++; return Operator(OPERATOR_ADDITION, 0, 10);
        case '-': _index++; return Operator(OPERATOR_SUBTRACTION, 0, 10);
        case '*': _index++; return Operator(OPERATOR_MULTIPLICATION, 0, 20);
        case '/': _index++; return Operator(OPERATOR_DIVISION, 0, 20);
        case ')': return Operator(OPERATOR_NULL, 0, 0);
            
        default:
            
            if (isEnd()) {
                return Operator(OPERATOR_NULL, 0, 0);
            }
            throw caculator_error(_expr, "unexceped format");
            break;
    }
}

int ExpressionParser::caculate(Operator op, int v1, int v2) {
    switch (op.op) {
        case OPERATOR_ADDITION:       return v1 + v2;
        case OPERATOR_SUBTRACTION:    return v1 - v2;
        case OPERATOR_MULTIPLICATION: return v1 * v2;
        case OPERATOR_DIVISION:       return v1 / checkZero(v2);
        default:
            throw caculator_error(_expr, "unexceped format");
            break;
    }
}

int ExpressionParser::checkZero(int value) {
    if (value == 0) {
        throw caculator_error(_expr, "Divided by 0");
    }
    return value;
}

char ExpressionParser::getCharacter() {
    if (isEnd()) {
        return 0;
    }
    return _expr[_index];
}

void ExpressionParser::eatSpace() {
    while (isspace(getCharacter()) != 0) {
        _index++;
    }
}

bool ExpressionParser::isEnd() {
    return _index >= _expr.size();
}