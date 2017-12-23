#include <functional>
#include <chrono>

using Time = std::chrono::steady_clock::time_point;
enum class Sound { Beep, Siren, Whistle };
using Duration = std::chrono::steady_clock::duration;
void SetAlarm(Time t, Sound s, Duration d) {
  /* do something */
}

// c++11
// SetSoundLambda is a function object allowing a sound to be specified
// for a 30-second alarm to go off
// an hour after it's set
auto SetSoundLambda = [](Sound s) {
  using namespace std::chrono;

  SetAlarm(steady_clock::now() + hours(1),
           s,
           seconds(30));
};

// c++14
auto SetSoundLambda2 = [](Sound s) {
  using namespace std::chrono;
  using namespace std::literals;  // for c++14 suffixes

  SetAlarm(steady_clock::now() + 1h,
           s,
           30s);
};

using namespace std::chrono;
using namespace std::literals;
using namespace std::placeholders;
// error!
// the alarm will be set to go off an hour
// after the call to std::bind,
// not an hour after the call to SetAlarm!
auto SetAlarmBind = std::bind(
    SetAlarm,
    steady_clock::now() + 1h,
    _1,
    30s);
// fix it
auto SetAlarmBind2 = std::bind(
    SetAlarm,
    std::bind(std::plus<>(),  // c++14, omit the template type argument for the standard operator templates
              std::bind(steady_clock::now),
              1h),
    _1,
    30s);
// fix it
auto SetAlarmBind3 = std::bind(
    SetAlarm,
    std::bind(std::plus<steady_clock::time_point>(),  // c++11, cannot omit the template type argument for the standard operator templates
              std::bind(steady_clock::now),
              1h),
    _1,
    30s);

enum class Volume { Normal, Loud, LoudPlusPlus };
// overload SetAlarm
void SetAlarm(Time t, Sound s, Duration d, Volume v) {
  /* do something */
}

// after overload SetAlarm,
// the SetAlarmLambda continue to work as before,
// because overload resolution choose the three-argument version of SetAlarm
auto SetSoundLambda2Copy = [](Sound s) {
  using namespace std::chrono;
  using namespace std::literals;  // for c++14 suffixes

  SetAlarm(steady_clock::now() + 1h,
           s,
           30s);
};

/*
// the bind call, on the other hand, now fails to compile 
auto SetAlarmBind2Copy = std::bind(
    SetAlarm,  // error! which SetAlarm?
    std::bind(std::plus<>(),  // c++14, omit the template type argument for the standard operator templates
              std::bind(steady_clock::now),
              1h),
    _1,
    30s);
*/
// fix it
using SetAlarm3ParamType = void(*)(Time t, Sound s, Duration d);
auto SetAlarmBind2CopyFixed = std::bind(
    static_cast<SetAlarm3ParamType>(SetAlarm),  // now okay
    std::bind(std::plus<>(),  // c++14, omit the template type argument for the standard operator templates
              std::bind(steady_clock::now),
              1h),
    _1,
    30s);

/*
// body of SetAlarm may well be inlined here
SetSoundLambda2(Sound::Siren);

// body of SetAlarm is less likely to be inlined here
SetAlarmBind2(Sound::Siren);
*/

auto low_value = 0, high_value = 100;
auto BetweenLambda = [low_value, high_value](const auto& val) {  // c++14
  return low_value <= val && val <= high_value;
};

auto BetweenBind = std::bind(
  std::logical_and<>(),  // c++14
  std::bind(std::less_equal<>(), low_value, _1),
  std::bind(std::less_equal<>(), _1, high_value));

auto BetweenBind2 = std::bind(
  std::logical_and<bool>(),  // c++11
  std::bind(std::less_equal<int>(), low_value, _1),
  std::bind(std::less_equal<int>(), _1, high_value));

auto BetweenLambda2 = [low_value, high_value](int val) {  // c++11
  return low_value <= val && val <= high_value;
};

enum class CompressionLevel { Low, Normal, High };
class Widget {};
Widget compress(const Widget& w, CompressionLevel level) {}
Widget w;
// how w is stored inside CompressionRateBind?
// It's stored by value.
// You must to remember how std::bind works
auto CompressionRateBind = std::bind(compress, w, _1);
// explicit as it is,
// w is captured by value
auto CompressionRateLambda = [w](CompressionLevel level) {
  return compress(w, level);
};
/*
// argument is pass by value
CompressionRateLambda(CompressionLevel::High);
// how is argument passed?
CompressionRateBind(CompressionLevel::high_value);
*/

// std::bind can be justified in two constained situation in c++11
// 1. move capture, see Item32
// 2. polymorphic function objects, see below
class PolyWidget {
 public:
  template<typename T>
      void operator()(const T& param) const {
        /* do something */
      }
};

PolyWidget pw;
auto bound_pw = std::bind(pw, _1);
/*
bound_pw(1930);  // pass int to PolyWidget::operator()
bound_pw(nullptr);  // pass nullptr ...
bound_pw("Rosebud");  // pass string literal ...
*/

int main() {
  return 0;
}
