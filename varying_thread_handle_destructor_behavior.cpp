#include <future>
#include <vector>

// this container might block in its destructor, because one or more
// contained futures could refer to a shared state  for a non-deferrd
// task launched via std::async
std::vector<future<void>> futures;

// Widget objects might blocks in their destructor
class Widget {
 public:

 private:
  std::shared_future<double> future_;
};

int CalcVal() {}

int main() {  
  std::packaged_task<int()> pt(CalcVal);  // wrap CalcVal so it can run asynchronously
  // the future future1 doesn't refer to a shared state created a call 
  // to std::async, so its destructor will behave normally.
  auto future1 = pt.get_future();  //  get future for pt
 
  {  // begin block
    std::packaged_task<int()> pt2(CalcVal);
    auto future2 = pt.get_future();
    // std::packaged_tasks aren't copyable
    std::thread t(std::move(pt));

    /* ... */  // see below
    // there are three basic possibilities to what can
    // happen to t inside the "..." region
    // 1. nothing happens to t
    // 2. a join is done on t
    // 3. a detach is done to t
  } 
  return 0;
}
