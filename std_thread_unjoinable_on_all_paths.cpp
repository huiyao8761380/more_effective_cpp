#include <vector>
#include <functional>
#include <thread>

constexpr auto ten_million = 100000000;
constexpr auto one_milion = 1'000'000;

bool DoWork(std::function<bool(int)> filter,
            int max_val = ten_million) {
  std::vector<int> good_vals;
  std::thread t([&filter, max_val, &good_vals] {
    for (auto i = 0; i <= max_val; ++i) {
      if (filter(i))
        good_vals.push_back(i);
    }
  });
  auto native_handle = t.native_handle();
  // if ConditionsAreSatisfied() return true, all is well.
  // but if it returns false or throws an exception, the std::thread object t
  // will be joinable when its destructor is called at the end of DoWork.
  // That would cause the program execution to be terminated.
  if (/*ConditionsAreSatisfied()*/1) {
    t.join();
    /* PerformComputation(good_vals) */
    return true;
  }

  return false;
}

// fix it using RAII
class ThreadRAII {
 public:
  enum class  DestructorAction { kJoin, kDetach };

  ThreadRAII(std::thread&& t, DestructorAction action)
    : action_(action), t_(std::move(t)) {}

  ThreadRAII(ThreadRAII&&) = default;
  ThreadRAII& operator=(ThreadRAII&&) = default;

  ~ThreadRAII() {
    if (t_.joinable()) {
      if (action_ == DestructorAction::kJoin) {
        t_.join();
      } else {
        t_.detach();
      }
    }
  }

  std::thread& get() { return t_; }
 private:
  DestructorAction action_;
  std::thread t_;
};

// fix it
bool DoWorkFixed(std::function<bool(int)> filter,
            int max_val = ten_million) {
  std::vector<int> good_vals;
  ThreadRAII t(std::thread([&filter, max_val, &good_vals] {
                 for (auto i = 0; i <= max_val; ++i) {
                   if (filter(i))
                     good_vals.push_back(i);
                 }
               }),
               ThreadRAII::DestructorAction::kJoin);

  auto native_handle = t.get().native_handle();
  if (/*ConditionsAreSatisfied()*/1) {
    t.get().join();
    /* PerformComputation(good_vals) */
    return true;
  }

  return false;
}

int main() {
  return 0;
}
