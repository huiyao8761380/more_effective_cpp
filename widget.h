#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <memory>

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
#endif
