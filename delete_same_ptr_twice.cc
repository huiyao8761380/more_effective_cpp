#include <iostream>

int main() {
  int* pi = new int(5);
  std::cout << *pi << '\n';
  delete pi;
//  delete pi;   // error!
  
  int* pd = nullptr;
  delete pd;

  return 0;
}
