// ProblemSolving.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <stack> // STL
#include "BinarySearch.h"
using namespace std;


// ----------------Problem : reverse a string----------------
// time complexity = O(n), space complexity = O(n)
void reverseStringUsingStack(string& input) {
    int length = input.length();
    stack<char> stck;

    for (int i = 0; i < length; i++) {
        stck.push(input[i]); // O(1) operation
    }

    for (int i = 0; i < length; i++) {
        char c = stck.top(); // O(1) operation
        input[i] = c;
        stck.pop(); // O(1) operation
    }
}

// time complexity = O(n), space complexity = O(1)
void reverseString(string& input) {
    int i = 0;
    int j = input.length() - 1;

    while (i < j) {
        char temp = input[i];
        input[i] = input[j];
        input[j] = temp;
        i++;
        j--;
    }
}

// ------------- Problem : Search for a string inside a string strStr() -----------------
// time complexity = O(m*n) - naive solution
bool compare(string haystack, string needle, int startIndex, int endIndex) {
    bool isEqual = true;
    for (int i = startIndex; i <= endIndex; i++) {
        if (haystack[i] != needle[i - startIndex]) {
            isEqual = false;
            break;
        }
    }
    return isEqual;
}

int strStr(string haystack, string needle) {
    int index = 0;
    int haySize = haystack.size();
    int needleSize = needle.size();
    if (needleSize == 0) {
        return 0;
    }
    int foundIndex = -1;
    while ((index + needleSize - 1) < haySize) {
        bool retVal = compare(haystack, needle, index, (index + needleSize - 1));
        if (retVal) {
            foundIndex = index;
            break;
        }
        index = index + 1;
    }
    return foundIndex;
}

// -------------Problem : Check for balanced paranthesis -------------------
// time complexity = O(n), space complexity = O(n)
bool areParanthesisClosedProperly(char opening, char closing) {
    if (opening == '(' && closing == ')') return true;
    else if (opening == '{' && closing == '}') return true;
    else if (opening == '[' && closing == ']') return true;
    return false;
}

bool isExpressionBalanced(string& expression) {
    int length = expression.length();
    stack<char> paranthesisStack;
    for (int i = 0; i < length; i++) {
        if (expression[i] == '(' || expression[i] == '{' || expression[i] == '[') {
            paranthesisStack.push(expression[i]);
        }
        else if (expression[i] == ')' || expression[i] == '}' || expression[i] == ']') {
            if (paranthesisStack.empty() || !areParanthesisClosedProperly(paranthesisStack.top(), expression[i])) {
                return false;
            }
            else {
                paranthesisStack.pop();
            }
        }
    }
    return paranthesisStack.empty();
}

// --------------Problem : Convert an Infix notation to Postfix notation, Evaluate a Postfix Notation ------------------
// (A+B)*C-D (Infix Notation) ------> AB+C*D- (Postfix Notation)
bool isOperator(char symbol) {
    if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/') {
        return true;
    }
    return false;
}

bool isParanthesis(char symbol) {
    if (symbol == '(' || symbol == ')') {
        return true;
    }
    return false;
}

bool hasMorePrecendence(char stckTop, char expElement) {
    if ((expElement == '*' || expElement == '/') && (stckTop == '+' || stckTop == '-')) {
        return false;
    }
    return true;
}

string convertInfixToPostfix(string& exp) {
    string postFixNotation = "";
    if (exp == "") { return postFixNotation; }

    stack<char> stck;
    int length = exp.length();
    for (int i = 0; i < length; i++) {
        if (!isOperator(exp[i]) && !isParanthesis(exp[i])) {
            postFixNotation += exp[i];
        }
        else if (isOperator(exp[i])) {
            while (!stck.empty() && stck.top() != '(' && hasMorePrecendence(stck.top(), exp[i])) {
                char top = stck.top();
                postFixNotation += top;
                stck.pop();
            }
            stck.push(exp[i]);
        }
        else if (exp[i] == ')' || exp[i] == '(') {
            if (exp[i] == ')') {
                while (stck.top() != '(') {
                    char top = stck.top();
                    postFixNotation += top;
                    stck.pop();
                }
                stck.pop();
            }
            else {
                stck.push(exp[i]);
            }
        }
    }

    while (!stck.empty()) {
        char top = stck.top();
        postFixNotation += top;
        stck.pop();
    }
    return postFixNotation;
}

int calculateExpression(int operand1, int operand2, char opr) {
    int op1 = operand1; // converting character representation of number into int number. 
    int op2 = operand2;
    int res = 0;
    if (opr == '*') { res = op1 * op2; }
    else if (opr == '/') { res = op1 / op2; }
    else if (opr == '+') { res = op1 + op2; }
    else if (opr == '-') { res = op1 - op2; }
    return res;
}

int evaluatePostfixExpression(string exp) {
    if (exp == "") { return 0; }
    int length = exp.length();
    stack<int> stck;

    for (int i = 0; i < length; i++) {
        if (!isOperator(exp[i])) {
            stck.push(exp[i] - '0'); // converting a char representation to decimal. '0' = 48, '1' = 49, etc in C++.
        }
        else {
            // operand2 is on top of stack in postfix expression - will affect in case of subtraction, i.e, a-b != b-a
            int operand2 = stck.top();
            stck.pop();
            int operand1 = stck.top();
            stck.pop();
            int res = calculateExpression(operand1, operand2, exp[i]);
            stck.push(res);
        }
    }

    return stck.top();
}


int main()
{
#pragma region reversing a string
    //string input;
    //cout << "Enter string : " << endl;
    //getline(cin, input);
    //reverseString(input);
    //cout << input;
#pragma endregion

#pragma region check for balanced paranthesis
    //string expression;
    //cout << "Enter an expression to evaluate : " << endl;
    //getline(cin, expression);

    //cout << "Paranthesis balanced = " << isExpressionBalanced(expression) << endl;
#pragma endregion

#pragma region Expression Conversion and Evaluation (Infix -> Postfix)
    //string infixExp;
    //cout << "Enter and infix expression : " << endl;
    //cin >> infixExp;
    //string result = convertInfixToPostfix(infixExp);
    //cout << "Postfix expression : " << result << endl;

    //int evaluatedExp = evaluatePostfixExpression(result);
    //cout << "Result of Expression : " << evaluatedExp << endl;
#pragma endregion

#pragma region Searching string inside a string - T(n) = O(m*n)
    //int retVal = strStr("hello", "ll");
#pragma endregion

#pragma region Search an element in a sorted list - return index if found or suggest the index to insert
    //vector<int> v{  };
    //searchInsert(v, 0);
#pragma endregion


}