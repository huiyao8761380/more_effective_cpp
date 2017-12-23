#include <memory>
#include <iostream>

class Investment {
 public:
  virtual ~Investment() {}
};

class Stock : public Investment {
 public:

};

class Bond : public Investment {
 public:

};

class RealEstate : public Investment {
 public:

};

void MakeLogEntry(Investment *pInvestment) {
  // TODO: fill this function body
}

template<typename... Ts>
std::unique_ptr<Investment>
makeInvestment(Ts&&... params)
{
  auto delete_investment = [](Investment *pInvestment) {
    MakeLogEntry(pInvestment);
    delete pInvestment;
  };
  std::unique_ptr<Investment, decltype(delete_investment)>
    pInvestment(nullptr, delete_investment);
  if (/*Stock*/1) {
    pInvestment.reset(new Stock(std::forward<Ts>(params)...));
  } else if (/*Bond*/1) {
    pInvestment.reset(new Bond(std::forward<Ts>(params)...));
  } else if (/*RealEstate*/1) {
    pInvestment.reset(new RealEstate(std::forward<Ts>(params)...));
  }
  return pInvestment;
}

int main() {
  std::unique_ptr<Bond> upbond = std::make_unique<Bond>();
  return 0;
}
