#include <memory>
#include <string>
#include <vector>

class Gadget {
 private:
  int id_;
};

class Widget {
 public:
  Widget();
  ~Widget();
 
  Widget(const Widget &rhs);
  Widget& operator=(const Widget &rhs);

  Widget(Widget &&rhs);
  Widget& operator=(Widget &&rhs);
 
 private:
  struct implementation;
  std::unique_ptr<implementation> implementation_ptr;
};

struct Widget::implementation {
  std::string name;
  std::vector<double> data;
  Gadget g1, g2, g3;
};

Widget::Widget() : implementation_ptr(std::make_unique<implementation>()) {}
Widget::~Widget() = default;

Widget::Widget(const Widget &rhs) : implementation_ptr(nullptr) {
  if (rhs.implementation_ptr)
    implementation_ptr = std::make_unique<implementation>(*rhs.implementation_ptr);
}
Widget& Widget::operator=(const Widget &rhs) {
  if (!rhs.implementation_ptr)
    implementation_ptr.reset();
  else if (!implementation_ptr)
    implementation_ptr = std::make_unique<implementation>(*rhs.implementation_ptr);
  else
    *implementation_ptr = *rhs.implementation_ptr;

  return *this;
}

Widget::Widget(Widget &&rhs) = default;
Widget& Widget::operator=(Widget &&rhs) = default;

int main() {
  Widget w1;
  auto w2(std::move(w1));
  w1 = std::move(w2); 
  return 0;
}
