#include <iostream>

class UPNumber {
 public:
  UPNumber();
  UPNumber(int);
  UPNumber(double);
  UPNumber(const UPNumber&);

  // pseudo destructor
  void Destroy() const {
    delete this;
  }

 //private:
 //protected:
 public:
  ~UPNumber();
 private:
  static void *operator new(size_t);
  static void operator delete(void*);
};

class NonNegativeUPNumber : public UPNumber {
 public:

};

class Asset {
 public:

 private:
  UPNumber* value;
};

int main() {
  UPNumber n;
  UPNumber* p = new UPNumber;
  // delete p;
  p->Destroy();

  NonNegativeUPNumber nn;
  Asset a;
  return 0;
}
