#include <atomic>
#include <iostream>

int main() {
  // during execution of these statements,
  // other threads reading ai may see only values of 
  // 0, 10, or 11, no other values are possible.
  std::atomic<int> ai(0);
  ai = 10;
  std::cout << ai;
  ++ai;
  --ai;

  // during execution of these statements,
  // if other threads are reading the value of ai,
  // they may see anything, e.g, -12, 68.
  volatile int vi(0);
  vi = 10;
  std::cout << vi;
  ++vi;
  --vi;

  int nx;  // memory behave normally
  auto ny = nx;
  ny = nx;  // compiler can optimize this

  nx = 10;
  nx = 20;  // compiler can eliminate the first one

  // special momory, compiler can't perform any optimizations on perations on this memory
  volatile int vx;
  auto vy = vx;
  vy = vx;  // can't be optimized away
  
  vx = 10;
  vx = 20;  // compiler can't eliminate this

  std::atomic<int> ax;
  // error, can't call deleted copy constructor.
  //auto ay = ax;  // conceptually read x
  //ay = ax;  // conceptually read x again
  //ax = 10;  // write x
  //ax = 20;  // write x again

  std::atomic<int> ay(ax.load());
  ay.store(ax.load());

  return 0;
}
