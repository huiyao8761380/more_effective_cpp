#include <vector>
#include <future>
#include <thread>

std::promise<void> p;

void react() {}

void detect() {
  auto sf = p.get_future().share();
  std::vector<std::thread> vt;
  for (int i = 0; i < 10; ++i) {
    vt.emplace_back([sf] {
      sf.wait();
      react();
      });
  }
  
  p.set_value();

  for (auto& t : vt) {
    t.join();
  }
}

int main() {
  detect();
  return 0;
}
