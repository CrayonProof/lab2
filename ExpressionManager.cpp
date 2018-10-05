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

bool isBracketOpen(string bracket)
{
    if (bracket == "(" || bracket == "{" || bracket == "[")
    {
        return true;
    }
    return false;
}

bool isBracketClosed(string bracket)
{
    if (bracket == ")" || bracket == "}" || bracket == "]")
    {
        return true;
    }
    return false;
}

bool is_of_some(string encompassing_string, const string s){
  return s.find_first_not_of(encompassing_string) == string::npos;
}

int getOperatorPrecedence(string op)
{
    if(is_of_some("*/%", op))
    {
        return 1;
    }
    else if(is_of_some("+-", op))
    {
        return 2;
    }
    else
    {
        return 3;
    }
}

bool process_operator(stack<string> &opStack, string &postfix, string &op)
{
    //cout << "postfix str: " << "\"" << postfix << "\"" << endl;
    //cout << "op str: " << "\"" << op << "\"" << endl;
    if (!opStack.empty())
    {
        if(opStack.empty() || isBracketOpen(opStack.top()) || isBracketOpen(op))
        {
            opStack.push(op);
            return true;
        }
        else if(isBracketClosed(op))
        {
            /*
            while (true)
            {
                if (!opStack.empty())
                {
                    if (getCounterpart(opStack.top().at(0)) != op.at(0))
                    {
                        postfix = postfix + opStack.top() + " ";
                        opStack.pop();
                    }
                    else
                    {
                        opStack.pop();
                        return true;
                        break;
                    }
                }
                else
                { 
                    cout << "operator that returned false: " << "\"" << op << "\"" << endl;
                    return false; //this is being returned when it shouldnt
                }
            }
                
                opStack.pop();
                return true;
            */
            while (getCounterpart(opStack.top().at(0)) != op.at(0)) //maybe something wrong with comparison
            {
                postfix = postfix + opStack.top() + " ";
                opStack.pop();
                if (opStack.empty())
                    return false;
            }
            opStack.pop();
            return true;
            
        }
        else
        {
            while (getOperatorPrecedence(op) >= getOperatorPrecedence(opStack.top()))
            {
                postfix = postfix + opStack.top() + " ";
                opStack.pop();
                if (opStack.empty())
                    break;
            }
            opStack.push(op);
            return true;
        }
    }
    opStack.push(op);
    return true;
}

//SEGMENTATION FAULT SOMEWHERE ABOVE

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
            else if (getCounterpart(expEval.top()) == c)
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
    
    if (!is_of_some("1234567890", tokens.at(0).substr(0, 1)))
    {
        return "invalid";
    }
    
    for (string s : tokens)
    {
        if(is_of_some(s, "."))
            return "invalid";
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
            /*DEBUGGING PURPOSES ONLY, PRINT STACK
            
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
            
            if (opperands.size() == 2)
            {
                string opp2 = opperands.top();
                opperands.pop();
                string opp1 = opperands.top();
                opperands.pop();
                opperands.push("( " + opp1 + " " + sStr0 + " " + opp2 + " )");
            }
            else
            {
                return "invalid";
            }
        }
        else
        {
            cout << "hello there was an error 1" << endl;
            return "invalid";
        }
    }
    if(opperands.size() == 1)
        return (opperands.top());
    else
        return "invalid";
}

string ExpressionManager::postfixEvaluate(string postfixExpression)
{
    stack<int> opperands;
    vector<string> tokens = parseTokens(postfixExpression);
    
    if (!is_of_some("1234567890", tokens.at(0).substr(0, 1)))
    {
        return "invalid";
    }
    
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
                
                if ((opp2 == 0 && sStr0 == "/"))
                    return "invalid";
                    
                opperands.push(evaluate(opp1, opp2, sStr0));
            }
        }
        else
        {
            cout << "hello there was an error 2" << endl;
            return "invalid";
        }
    }
    if(!opperands.empty())
        return (to_string(opperands.top()));
}

string ExpressionManager::infixToPostfix(string infixExpression)
{
    string postfix = "";
    stack<string> opperators;
    //opperators.push(" ");
    //opperators.pop();
    vector<string> tokens = parseTokens(infixExpression);
    
    if (is_of_some("+-/*%", tokens.at(0).substr(0, 1)))
    {
        return "invalid";
    }
    
     for (string s : tokens)
    {
        if(is_of_some(s, "."))
            return "invalid";
        
        string sStr0 = s.substr(0, 1);
        
        if (sStr0 == "")
        {
            cout << "surprise sStr0 = \"\"" << endl;
        }
        else if (is_of_some("1234567890", sStr0))
        {
            postfix = postfix + s + " ";
        }
        else if (is_of_some("(+-/*%)", sStr0))
        {
            if (!process_operator(opperators, postfix, sStr0))
            {
                cout << "process operator error my lad" << endl;
            }
        }
        else
        {
            cout << "hello there was an error 3: " << sStr0 << endl;
            return "invalid";
        }
    }
    while (!opperators.empty())
    {
        postfix = postfix + opperators.top();
        opperators.pop();
        if (opperators.size() > 0)
        {
            postfix = postfix + " ";
        }
    }
    if (!isBalanced(postfix))
    {
        postfix = "Wow " + postfix;
            cout << "invalid postfix after conversion from in to post" << endl;
    }
    return postfix;
}

