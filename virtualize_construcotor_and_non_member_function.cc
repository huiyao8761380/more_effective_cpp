#include <list>
#include <iostream>

class NLComponent {
 public:
 // virtual copy constructor
 virtual NLComponent* clone() const = 0;
 virtual std::ostream& print(std::ostream& os) const = 0;
};

class TextBlock: public NLComponent {
 public:
  virtual TextBlock* clone() const {
    return new TextBlock(*this);
  }
  virtual std::ostream& print(std::ostream& os) const;
};

class Graphic: public NLComponent {
 public:
  virtual Graphic* clone() const {
    return new Graphic(*this);
  }
  virtual std::ostream& print(std::ostream& os) const;
};

class NewsLetter {
 public:
  NewsLetter(std::istream& is);
  NewsLetter(const NewsLetter& rhs);
 private:
  static NLComponent* ReadComponent(std::istream& is);
  std::list<NLComponent*> components;
};

NewsLetter::NewsLetter(std::istream& is) {
  while (is) {
    components.push_back(ReadComponent(is));
  }
}

NewsLetter::NewsLetter(const NewsLetter& rhs) {
  for (auto it = rhs.components.cbegin(); it != rhs.components.cend(); ++it) {
    components.push_back((*it)->clone());
  }
}

NLComponent* NewsLetter::ReadComponent(std::istream& is) {
  // read the next component object from is
  return nullptr;  // just for test
}

inline std::ostream& operator<<(std::ostream& os, const NLComponent& c) {
  return c.print(os);
}

int main() {
  return 0;
}
