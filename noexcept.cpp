#include <iostream>

//int f(int) throw() {  }// no exception from f: c++98 style
//int f2(int) noexcept {  }// no exception from f2: c++11 style

//void f3() noexcept {  } // most optimizable
void f4() throw() {  } // less optimizable
//void f5() { } // less optimizable

int main()
{
//	f3();
	f4();
//	f5();
	return 0;
}
