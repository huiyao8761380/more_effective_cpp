#include <memory>
#include <iostream>
#include <vector>
class Widget {};
void ProcessWidget(std::shared_ptr<Widget> /*spw*/, int /*priority*/) {}
int ComputePriority() { return 1; }

int main() {
  auto upw(std::make_unique<Widget>());
  std::unique_ptr<Widget> upw2(new Widget);// code duplication for 'Widget'
  ProcessWidget(std::shared_ptr<Widget>(new Widget),
                ComputePriority());// potential resource leak!
  ProcessWidget(std::make_shared<Widget>(),
                ComputePriority());// no potential resource leak!
  auto upv = std::make_unique<std::vector<int>>(10, 42);
  std::cout << upv->at(0) << '\n';
  auto initlist = {10, 42};
  auto upv2 = std::make_unique<std::vector<int>>(initlist);
  std::cout << upv2->at(0) << '\n';

  auto CustomDeleter = [](Widget *p) {
    delete p;
  };
  std::shared_ptr<Widget> spw(new Widget, CustomDeleter);
  ProcessWidget(std::move(spw), ComputePriority());// both efficient and exception safe
  return 0;  
}
