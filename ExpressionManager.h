#pragma once
#include <iostream>
#include <string>
#include <stack>
#include "ExpressionManagerInterface.h"

using namespace std;


class ExpressionManager :
    public ExpressionManagerInterface
{
public:
	ExpressionManager();
	 ~ExpressionManager();
    bool isBalanced(string expression);
    string postfixToInfix(string postfixExpression);
    string postfixEvaluate(string postfixExpression);
    string infixToPostfix(string infixExpression);

};