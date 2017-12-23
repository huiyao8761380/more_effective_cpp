#include <functional>
#include <vector>
using filter_container = std::vector<std::function<bool(int)>>;
filter_container filters;
filters.emplace_back([](int value) {return value % 5 == 0; });

void AddDivisorFilter() {
  auto calc1 = /*ComputeSomeValue1()*/1;
  auto calc2 = /*ComputeSomeValue1()*/2;
  auto divisor = /*ComputeDivisor(calc1, calc2)*/calc1 + calc2;
  filters.emplace_back([&](int value) {
    return value % divisor == 0;
  });
}

int main() {
  return 0;
}
