#include <memory>
#include <iostream>
#include <unordered_map>

class Widget {};
struct WidgetID {};
std::unique_ptr<const Widget> LoadWidget(WidgetID /*id*/) {}
std::shared_ptr<const Widget> FastLoadWidget(WidgetID id) {
  static std::unordered_map<WidgetID, std::weak_ptr<const Widget>> cache;
  auto spw = cache[id].lock();
  if (!spw) {
    spw = LoadWidget(id);
    cache[id] = spw;
  }
  return spw;
}
int main() {
  auto spw = std::make_shared<Widget>();
  std::cout << spw.use_count() << '\n';
  std::weak_ptr<Widget> wpw(spw);
  std::cout << spw.use_count() << '\n';
  std::cout << wpw.use_count() << '\n';
  spw = nullptr;
  std::cout << spw.use_count() << '\n';
  if (wpw.expired())
    std::cout << "expired\n";

  auto spw2 = wpw.lock();
  std::shared_ptr<Widget> spw3(wpw);
  return 0;
}
