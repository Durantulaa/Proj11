#include "calc.h"
#include <iostream>

using namespace std;
int main(int argc, char *argv[]) {

  if (argc != 2) {
    cout << "Invalid input. Please try again." << endl;
    return 1;
  }

  Calc *C = new Calc(argv[1]);

  // Test CheckTokens with valid input
  // Calc calculator1(argv[1]);

  if (!C->CheckTokens()) {
    cout << "CheckTokens test failed\n";
  } else {
    cout << "CheckTokens test passed\n";
  }

  if (!C->CheckParens()) {
    cout << "CheckParens test failed\n";
  } else {
    cout << "CheckParens test passed\n";
  }

  C->Parse();
  C->DisplayInFix();
  

  return 0;
}