// #include "calc.h"
// #include <iostream>

// using namespace std;

// int main(int argc, char *argv[]) {
//   if (argc != 2) {
//     cout << "Invalid input. Please try again." << endl;
//     return 1;
//   }

//   Calc *C = new Calc(argv[1]);

//   if (C->CheckTokens()) {
//     cout << "CheckTokens test passed\n";
//   } else {
//     cout << "CheckTokens test failed\n";
//   }

//   if (C->CheckParens()) {
//     cout << "CheckParens test passed\n";
//   } else {
//     cout << "CheckParens test failed\n";
//   }

//   C->Parse();
//   C->DisplayInFix();
//   C->InFixToPostFix();
//   C->DisplayPostFix();
//   cout << "Evaluation: " << C->Evaluate() << endl;

//   // Test private functions
//   C->MakeValueTbl();
//   C->FindLast(0);
//   C->InFixToPostFix();

//   delete C; // Don't forget to delete the object to avoid memory leaks

//   return 0;
// }
#include <iostream>
using namespace std;

#include "calc.h"

int main(int argc, char *argv[]) {
  Calc *C = new Calc(argv[1]);

  C->DisplayInFix();
  //C->InFixToPostFix();
  C->DisplayPostFix();

  int result = C->Evaluate();
  cout << "Evaluation: " << result << endl;
  // cout << "Evaluation: " << C->Evaluate() << endl;

  delete C;
  return 0;
}
