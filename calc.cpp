/*
Name: Fady Youssef
Class: CPSC 122, Section 1
Date Submitted: April 24, 2024
=Description: Part 2 of Calculator Assignment 
To Compile: make
To Execute: ./calc "(121+12)"
*/

#include "calc.h"
#include <cctype>  // Include cctype for isdigit and isalpha
#include <cstdlib> // Include cstdlib for exit function
#include <cstring>
#include <iostream>

using namespace std;

Calc::Calc(const char *argvIn) {
  stk = new Stack();

  int len = strlen(argvIn);
  inFix = new char[len + 1];   // Add 1 for the null terminator
  postFix = new char[len + 1]; // Add 1 for the null terminator

  strcpy(inFix, argvIn);

  if (!CheckTokens())
    cout << "invalid token input\n";
  else
    cout << "Tokens Balanced\n";
  if (!CheckParens())
    cout << "invalid parens input\n";
  else
    cout << "Parens Balanced\n";

  MakeValueTbl();
  Parse();
  InFixToPostFix();
}

Calc::~Calc() {
  delete[] inFix;
  delete[] postFix;
  delete[] valueTbl;
}

void Calc::MakeValueTbl() {
  valueTbl = new int[26];
  for (int i = 0; i < 26; i++)
    valueTbl[i] = 0;
}

int Calc::FindLast(int cur) {

  int last = cur;
  while (isdigit(inFix[last])) {
    last++;
  }
  return last - 1; // return last digit
}

bool Calc::CheckParens() {
  bool bal = true;
  int i = 0;
  char ch = inFix[i];
  while (bal && ch != '\0') {
    if (ch == '(')
      stk->Push(ch);
    else if (ch == ')') {
      if (!stk->IsEmpty())
        stk->Pop();
      else
        bal = false;
    }
    i++;
    ch = inFix[i];
  }
  if (bal && stk->IsEmpty())
    return true;
  return false;
}

bool Calc::CheckTokens() {
  for (int i = 0; inFix[i] != '\0'; i++) {
    if (!(inFix[i] == '+' || inFix[i] == '-' || inFix[i] == '*' ||
          inFix[i] == '(' || inFix[i] == ')' ||
          ((isalpha(inFix[i]) && isupper(inFix[i]))) || isdigit(inFix[i]))) {
      cout << "Invalid Input\n";
      return false;
    }
  }
  return true;
}

void Calc::Parse() {
  MakeValueTbl(); // initialize value table
  int i = 0;
  int j = 0;
  int last = 0;

  while (inFix[i] != '\0') {
    if (inFix[i] == '(') {
      inFix[j++] = inFix[i];
      stk->Push(inFix[i]);
    } else if (inFix[i] == ')') {
      while (stk->Peek() != '(') {
        inFix[j++] = stk->Peek();
        stk->Pop();
      }
      inFix[j++] = inFix[i];
      stk->Pop();
    }

    else if (isdigit(inFix[i])) {
      last = FindLast(i);
      int num = 0;
      for (int k = i; k <= last; k++) {
        num = num * 10 + (inFix[k] - '0');
      }
      inFix[j++] = 'A' + valueIdx;
      valueTbl[valueIdx++] = num;
      i = last;
    } else {
      inFix[j++] = inFix[i];
    }
    i++;
  }
  inFix[j] = '\0';
}

void Calc::InFixToPostFix() {
  char ch;
  int i = 0; // Add an index variable
  for (int j = 0; inFix[j] != '\0'; j++) {
    ch = inFix[j];
    if (isdigit(ch) || isalpha(ch)) {
      postFix[i++] = ch; // Use indexing to access elements
    } else if (ch == '(') {
      stk->Push(ch);
    } else if (ch == '+' || ch == '-' || ch == '*') {
      stk->Push(ch);
    } else if (ch == ')') {
      while (!stk->IsEmpty() && stk->Peek() != '(') {
        postFix[i++] = stk->Peek(); // Use indexing to access elements
        stk->Pop();
      }
      stk->Pop(); // Pop '('
    }
  }
  postFix[i] = '\0'; // Add null terminator at the end
}

int Calc::Evaluate() {
  InFixToPostFix(); // Convert infix expression to postfix
  char ch;
  int op1, op2;
  for (int i = 0; postFix[i] != '\0';
       i++) { // Loop through the postfix expression
    ch = postFix[i];
    if (isalpha(ch)) {
      stk->Push(
          valueTbl[ch - 'A']); // Push the value of the variable onto the stack
    } else if (isdigit(ch)) {
      stk->Push(ch - '0'); // Push the digit onto the stack
    } else if (ch == '+' || ch == '-' || ch == '*') {
      op2 = stk->Pop();
      op1 = stk->Pop();
      switch (ch) {
      case '+':
        stk->Push(op1 + op2);
        break;
      case '-':
        stk->Push(op1 - op2);
        break;
      case '*':
        stk->Push(op1 * op2);
        break;
      }
    }
  }
  int result = stk->Pop(); // Return the final result
  return result;
}

void Calc::DisplayPostFix() { cout << "PostFix: " << postFix << endl; }

void Calc::DisplayInFix() { cout << "InFix: " << inFix << endl; }
