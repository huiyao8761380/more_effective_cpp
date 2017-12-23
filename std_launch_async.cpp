#include <future>
using namespace std::literals;

void f() {}
void f2() { std::this_thread::sleep_for(1s); }

// c++11 version
template<typename F, typename... Ts>
inline
std::future<typename std::result_of<F(Ts...)>::type>
ReallyAsync(F&& f, Ts&&... params) {
  return std::async(std::launch::async,  // return future for asynchronous call to f(params...)
                    std::forward<F>(f),
                    std::forward<Ts>(params)...);
}
// c++14 version
template<typename F, typename... Ts>
inline
auto
ReallyAsync2(F&& f, Ts&&... params) {
  return std::async(std::launch::async,  // return future for asynchronous call to f(params...)
                    std::forward<F>(f),
                    std::forward<Ts>(params)...);
}

int main() {
  // the following two calls have exactly the same meaning.
  auto future1 = std::async(f);  // run f using default launch policy
  auto future2 = std::async(std::launch::async |
                            std::launch::deferred,
                            f);  // run f either async or deferred
  // run f asynchronously (conceptually)
  auto future3 = std::async(f2);
  // loop until f has finished running...
  // which may never happen
  while (future3.wait_for(100ms) !=
         std::future_status::ready) {
    /* do something */
  }
  // fix it
  if (future3.wait_for(0s) ==  // if task is deferred
      std::future_status::deferred) {
    /* use wait or get on future3 to call f synchronously */
  } else {  // task isn't deferred
    while (future3.wait_for(100ms) !=  // ifinite loop not possible (assuming f finishes)
           std::future_status::ready) {
      /* task is neither deferred nor ready, so do concurrent work until it's
       * ready */
    }
    // future3 is ready
  }

  auto future4 = std::async(std::launch::async, f);  // launch f asynchronously (truely)
  auto future5 = ReallyAsync(f);  // run f asynchronously, throw if std::async would throw
  return 0;
}
