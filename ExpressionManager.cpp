//#pragma once
#include <iostream>
#include <sstream> 
#include <string>
#include <stack>
#include <vector>
#include "ExpressionManager.h"

using namespace std;

ExpressionManager::ExpressionManager()
{
    
}

ExpressionManager::~ExpressionManager()
{
    
}

vector<string> parseTokens(string expression)
{
  stringstream ss(expression);
  string token;
  vector<string> tokens;
  while(getline(ss, token, ' '))
  {
    tokens.push_back(token);
  }
  return tokens;
}

char getCounterpart(char arg0)
{
    if (arg0 == '(')
    {
        return ')';
    }
    else if (arg0 == '[')
    {
        return ']';
    }
    else if (arg0 == '{')
    {
        return '}';
    }
    if (arg0 == ')')
    {
        return '(';
    }
    else if (arg0 == ']')
    {
        return '[';
    }
    else if (arg0 == '}')
    {
        return '{';
    }
}

int evaluate(int opp1, int opp2, string opperator)
{
    if (opp2 == 0 && opperator == "/")
    {
        return 0;
    }
    if (opperator == "+")
    {
        return opp1 + opp2;
    }
    if (opperator == "-")
    {
        return opp1 - opp2;
    }
    if (opperator == "*")
    {
        return opp1 * opp2;
    }
    if (opperator == "/")
    {
        return opp1 / opp2;
    }
    if (opperator == "%")
    {
        return opp1 % opp2;
    }
}

bool is_of_some(string encompassing_string, const string s){
  return s.find_first_not_of(encompassing_string) == string::npos;
}

bool ExpressionManager::isBalanced(string expression)
{
    stack<char> expEval;
    int index = 0;
    bool balanced = true;
    
    while(index < expression.length())
    {
        char c = expression.at(index);
        
        if (c == '(' || c == '{' || c == '[')
        {
            expEval.push(c);
        }
        else if (c == ')' || c == '}' || c == ']')
        {
            if (expEval.empty())
            {
                balanced = false;
                return false;
            }
            if (getCounterpart(expEval.top()) == c)
            {
                expEval.pop();
            }
            else
            {
                balanced = false;
                return false;
            }
        }
        
        index++;
    }
    if (expEval.empty())
        return true;
    return false;
}

string ExpressionManager::postfixToInfix(string postfixExpression)
{
    stack<string> opperands;
    vector<string> tokens = parseTokens(postfixExpression);
    
    for (string s : tokens)
    {
        string sStr0 = s.substr(0, 1); //grabs the first character, maybe suppsoed to be first string?
        
        //cout << "sStr0: " << "\"" << s << "\"" << endl;
        
        if (sStr0 == "")
        {
            cout << "surprise sStr0 = \"\"" << endl;
        }
        else if (is_of_some("1234567890", sStr0))
        {
            //cout << "sStr0: " << "\"" << sStr0 << "\"" << endl;
            opperands.push(s);
        }
        else if (is_of_some("+-/*%", sStr0))
        {
            /*DEBUGGING PURPOSES ONLY, PRINT VECTOR
            
            vector<int> viewStack;
            
            while (!opperands.empty())
            {
                viewStack.push_back(opperands.top());
                opperands.pop();
            }
            for (int i = viewStack.size() - 1; i >= 0; i--)
            {
                cout << viewStack.at(i) << ", ";
                opperands.push(viewStack.at(i));
            }
        
            cout << sStr0 << endl;
            
            DEBUGGING PURPOSES ONLY END
            */
            
            if (opperands.size() > 1)
            {
                string opp2 = opperands.top();
                opperands.pop();
                string opp1 = opperands.top();
                opperands.pop();
                opperands.push("( " + opp1 + " " + sStr0 + " " + opp2 + " )");
            }
        }
        else
        {
            cout << "hello there was an error" << endl;
        }
    }
    return (opperands.top());
}

string ExpressionManager::postfixEvaluate(string postfixExpression)
{
    stack<int> opperands;
    vector<string> tokens = parseTokens(postfixExpression);
    
    for (string s : tokens)
    {
        string sStr0 = s.substr(0, 1); //grabs the first character, maybe suppsoed to be first string?
        
        //cout << "sStr0: " << "\"" << s << "\"" << endl;
        
        if (sStr0 == "")
        {
            cout << "surprise sStr0 = \"\"" << endl;
        }
        else if (is_of_some("1234567890", sStr0))
        {
            //cout << "sStr0: " << "\"" << sStr0 << "\"" << endl;
            opperands.push(stoi(s));
        }
        else if (is_of_some("+-/*%", sStr0))
        {
            /*DEBUGGING PURPOSES ONLY, PRINT VECTOR
            
            vector<int> viewStack;
            
            while (!opperands.empty())
            {
                viewStack.push_back(opperands.top());
                opperands.pop();
            }
            for (int i = viewStack.size() - 1; i >= 0; i--)
            {
                cout << viewStack.at(i) << ", ";
                opperands.push(viewStack.at(i));
            }
        
            cout << sStr0 << endl;
            
            DEBUGGING PURPOSES ONLY END
            */
            
            if (opperands.size() > 1)
            {
                int opp2 = opperands.top();
                opperands.pop();
                int opp1 = opperands.top();
                opperands.pop();
                opperands.push(evaluate(opp1, opp2, sStr0));
            }
        }
        else
        {
            cout << "hello there was an error" << endl;
        }
    }
    return (to_string(opperands.top()));
}

string ExpressionManager::infixToPostfix(string infixExpression)
{
    
}

