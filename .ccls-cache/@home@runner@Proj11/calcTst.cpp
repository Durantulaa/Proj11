#include <iostream>
using namespace std;

#include "calc.h"

int main(int argc, char *argv[]) {
  
  Calc *C = new Calc(argv[1]);
  int result = C->Evaluate();

  C->DisplayInFix();
  C->DisplayPostFix();
  cout << "Evaluation: " << result << endl;

  delete C;
  return 0;
}
