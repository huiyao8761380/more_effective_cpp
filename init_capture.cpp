#include <memory>
#include <vector>
#include <functional>

class Widget {
 public:
  bool IsValidated() const { return true; }
  bool IsProcessed() const { return false; }
  bool IsArchived() const { return true; }
};

auto pw = std::make_unique<Widget>();
// configure *pw
/* configure(*pw);*/
auto func = [pw = std::move(pw)] {  // c++14, init capture
  return pw->IsValidated() &&
         pw->IsArchived();
};
// need not configure *pw
auto func2 = [pw = std::make_unique<Widget>()] {
  return pw->IsValidated() &&
         pw->IsArchived();
};

class IsValidatedAndArchived {
 public:
  using DataType = std::unique_ptr<Widget>;

  explicit IsValidatedAndArchived(DataType&& ptr)
    : pw(std::move(ptr)) {}

  bool operator()() const {
    return pw->IsValidated() && pw->IsArchived();
  }

 private:
  DataType pw;
};

// c++11
auto func3 = IsValidatedAndArchived(std::make_unique<Widget>());

int main() {
  std::vector<double> data;
  auto func4 = [data = std::move(data)] {  // c++14 init capture
    /* use of data */
  };
 
  // c++11 emulation of init capture, works on g++, but not work on clang++ 
  auto func5 = std::bind(
    [](const std::vector<double>& data) {
    /* use of data */
    },
    std::move(data)
  );
  // c++11 emulation of init capture for mutable lambda, works on g++, but not work on clang++ 
  auto func6 = std::bind(
    [](std::vector<double>& data) mutable {
    /* use of data */
    },
    std::move(data)
  );
  // c++11 emulation
  auto func7 = std::bind(
    [](const std::unique_ptr<Widget>& pw) {
    return pw->IsValidated() && pw->IsArchived();
    },
    std::make_unique<Widget>()
  );
  return 0;
}
