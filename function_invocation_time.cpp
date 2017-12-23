#include <vector>

class Widget {};

void f(Widget &&param) {} // rvalue reference
Widget &&var1 = Widget(); // rvalue reference
auto &&var2 = var1; // universal reference
template<typename T> void f2(std::vector<T> &&param) {} // rvalue reference
template<typename T> void f3(T &&param) {} // universal reference
template<typename T> void f4(const T &&param) {} // param is an rvalue reference

auto function_invocation_time = [](auto &&func, auto &&... params) {
  // start timer
  std::forward<decltype(func)>(func)(
    std::forward<decltype(params)>(params)...);
  // stop timer and record elapsed time
};

int main() {
  Widget w;
  // lvalue passed to f3; param's type is Widget& (i.e., an lvalue reference)
  f3(w);
  // rvalue passed to f3; param's type is Widget&& (i.e., an rvalue reference)
  f3(std::move(w)); 
  
  std::vector<int> v;
  // f2(v); // error
  
  int i = 0;
  // f4(i); // error
  return 0;
}

