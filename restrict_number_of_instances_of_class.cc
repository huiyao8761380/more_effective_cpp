#include <iostream>

class CantBeInstantiated {
 private:
  CantBeInstantiated();
  CantBeInstantiated(const CantBeInstantiated&);
};

namespace PrintingStuff {
  class PrintJob;
  class Printer {
    friend Printer& ThePrinter();
   public:
    class TooManyObjects {};
    // pseudo-constructor
    static Printer* MakePrinter();
    ~Printer();

    void SubmitJob(const PrintJob& job);
    void Reset();
    void PerformSelfTest();
   private:
    static size_t num_objects;
    static const size_t max_num_objects = 10; 
    Printer();
    Printer(const Printer& rhs);
  };

  Printer& ThePrinter() {
    static Printer p;
    return p;
  }

  size_t Printer::num_objects = 0;
  const size_t Printer::max_num_objects;

  Printer::Printer() {
    if (num_objects >= max_num_objects) {
      throw TooManyObjects();
    }
    // proceed with normal object construction here
    ++num_objects;
  }

  Printer* Printer::MakePrinter() {
    return new Printer();
  }
}  // namespace PrintingStuff

template<typename BeingCounted>
class Counted {
 public:
  class TooManyObjects{};
  static int ObjectCount() {
    return num_objects;
  }

 protected:
  Counted();
  Counted(const Counted& rhs);
  ~Counted() {
    --num_objects;
  }

 private:
  static int num_objects;
  static const size_t max_num_objects;
  void init();
};

template<typename BeingCounted>
int Counted<BeingCounted>::num_objects = 0;

template<typename BeingCounted>
const size_t Counted<BeingCounted>::max_num_objects = 10;


template<typename BeingCounted>
Counted<BeingCounted>::Counted() {
  init();
}

template<typename BeingCounted>
Counted<BeingCounted>::Counted(const Counted<BeingCounted>& rhs) {
  init();
}

template<typename BeingCounted>
void Counted<BeingCounted>::init() {
  if (num_objects >= max_num_objects) {
    throw TooManyObjects();
  }
  ++num_objects;
}

class Printer: private Counted<Printer> {
 public:
  // pseudo-constructor
  static Printer* MakePrinter();
  static Printer* MakePrinter(const Printer& rhs);
  
  ~Printer();

  void SubmitJob(const PrintingStuff::PrintJob& job);
  void Reset();
  void PerformSelfTest();
  
  using Counted<Printer>::ObjectCount;
  using Counted<Printer>::TooManyObjects;

 private:
  Printer();
  Printer(const Printer& ths);
};

Printer::Printer() {
  // proceed with normal object construction here
}

int main() {

  return 0;
}
