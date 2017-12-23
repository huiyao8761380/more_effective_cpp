#include "widget.h"
#include "gadget.h"
#include <string>
#include <vector>

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
