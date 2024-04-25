/*
Name: Fady Youssef
Class: CPSC 122, Section 1
Date Submitted: April 23, 2024
Description: Part 1 of Calculator Assignment
To Compile: make
To Execute: ./calc "(121+12)"
*/

#include "calc.h"
#include <cstddef>
#include <cstring>
#include <iostream>
#include <fstream>


using namespace std;

Calc::Calc(const char *argvIn) {
  stk = new Stack();
  valueTbl = new int[26];
  valueIdx = 0;
  int len = strlen(argvIn);
  inFix = new char[len + 1]; // Add 1 for the null terminator
  strcpy(inFix, argvIn);
}

Calc::~Calc() {
  delete[] inFix;
  delete[] valueTbl;
  delete stk;
} // done

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
} // done

void Calc::MakeValueTbl() {
  for (int i = 0; i < 26; i++)
    valueTbl[i] = 0;
}

int Calc::FindLast(int cur) {
  int last = cur;
  while (isdigit(inFix[last++])) {
    if (!isdigit(inFix[last]))
      return last;
  }
  return last; // return last digit
}
// parse the infix expression
void Calc::Parse() {
  MakeValueTbl(); // initialize value table
  int len = strlen(inFix);
  int i = 0; // initialize loop index
  while (i < len) {
    if (isalpha(inFix[i])) {
      // find the last index of the variable
      int lastIndex = FindLast(i);
      // convert variable to index in value table
      int varIndex = inFix[i] - 'A';
      // if variable hasn't been assigned a value, set it to zero
      if (valueTbl[varIndex] == 0) {
        valueTbl[varIndex] = 0;
      }
      // move to the next character after the variable
      i = lastIndex;
    } else {
      // move to the next character
      i++;
    }
  }
}

bool Calc::CheckParens() {
  int ct = 0;
  for (int i = 0; inFix[i] != '\0'; i++) {
    if (inFix[i] == '(')
      ct++; // on left
    else if (inFix[i] == ')')
      ct--; // on right
  }

  if (ct != 0) { // if ct is unbalanced
    cout << "Unbalanced parens\n";
    return false;
  }
  return true;
}

void Calc::DisplayInFix() { cout << "InFix: " << inFix << endl; }