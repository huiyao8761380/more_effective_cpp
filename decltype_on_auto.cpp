#include <iostream>

template<typename T>
T normalize(T x) {
  /* normalize(x) */
  return x;
}

auto f = [](auto x) {
  return normalize(x);
};

// the closure class's function call operator looks like this:
class SomeCompilerGeneratedClassName {
 public:
  template<typename T>
  auto operator()(T x) const {
    return normalize(x);
  }
};
/*
auto f2 = [](auto&& x) {
  return normalize(std::forward<???>(x));
};
*/
auto f3 = [](auto&& x) {
  return normalize(std::forward<decltype(x)>(x));
};
auto f4 = [](auto&&... xs) {
  return normalize(std::forward<decltype(xs)>(xs)...);
};




int main() {
  return 0;
}
