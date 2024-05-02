#include "calc.h"
#include <iostream>

using namespace std;
int main(int argc, char *argv[]) {

  if (argc != 2) {
    cout << "Invalid input. Please try again." << endl;
    return 1;
  }

  Calc *C = new Calc(argv[1]);

  if (C->CheckTokens()) {
    cout << "CheckTokens test passed\n";
  } else {
    cout << "CheckTokens test failed\n";
  }

  if (C->CheckParens()) {
    cout << "CheckParens test passed\n";
  } else {
    cout << "CheckParens test failed\n";
  }

  C->Parse();
  C->DisplayInFix();
  C->InFixToPostFix();
  C->DisplayPostFix();
  cout << "Evaluation: " << C->Evaluate() << endl;

  return 0;
}