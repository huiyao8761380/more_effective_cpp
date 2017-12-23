#include <thread>
#include <future>

int DoAsyncWork() { return 1; }

int main() {
  // if you want to run a function asynchronously,
  // you have two basic choices.
  // 1. thread-based approach
  // you have to do thread management manually.
  std::thread t(DoAsyncWork);
  // 2. task-based approach
  // the Standard Library takes care of thread management automatically.
  auto my_future = std::async(DoAsyncWork);
  return 0;
}
