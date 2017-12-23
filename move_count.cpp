#include <iostream>
#include <vector>
#include <string>

class Widget {
 public:
  Widget() = default;
  Widget(const Widget &rhs) : data(rhs.data) { ++num_of_copy_constructor_calls; }
  Widget(Widget &&rhs) : data(std::move(rhs.data)) { ++num_of_move_constructor_calls; } 
  std::size_t GetCopyCount() { return num_of_copy_constructor_calls; }
  std::size_t GetMoveCount() { return num_of_move_constructor_calls; }
 private:
  static std::size_t num_of_move_constructor_calls;// = 0;
  static std::size_t num_of_copy_constructor_calls;// = 0;
  std::vector<std::string> data;
};
std::size_t Widget::num_of_move_constructor_calls = 0;
std::size_t Widget::num_of_copy_constructor_calls = 0;

int main() {
  Widget w;
  std::cout << w.GetCopyCount() << ' ' << w.GetMoveCount() << '\n';
  Widget w2(std::move(w));
  std::cout << w2.GetCopyCount() << ' ' << w2.GetMoveCount() << '\n';
  Widget w3(w2);
  std::cout << w3.GetCopyCount() << ' ' << w3.GetMoveCount() << '\n';
  return 0;
}
