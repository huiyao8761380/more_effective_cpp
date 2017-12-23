#include <memory>

class Widget : public std::enable_shared_from_this<Widget> {
 public:
  // factory function that perfect-forward args
  // to a private constructor
  template<typename... Ts> static std::shared_ptr<Widget> create(Ts&&... params) {}
  void process() {}

 private:
  Widget() {}
};

int main() {
  return 0;
}
