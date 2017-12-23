#include <iostream>

class RCObject {
public:
 void AddReference();
 void RemoveReference();

 void MarkUnshareable();
 bool IsShareable() const;
 bool IsShared() const;

protected:
 RCObject();
 RCObject(const RCObject& rhs);
 RCObject& operator=(const RCObject& rhs);
 virtual ~RCObject() = 0;

private:
 int reference_count;
 bool shareable;
};

template<typename T>
class RCIPtr {
 public:
  RCIPtr(T* real_ptr = 0);
  RCIPtr(const RCIPtr& rhs);
  ~RCIPtr();

  RCIPtr& operator=(const RCIPtr& rhs);

  const T* operator->() const;
  T* operator->();
  const T& operator*() const;
  T& operator*();

 private:
  struct CountHolder: RCObject {
    ~CountHolder() {
      delete pointee;
    }
    T* pointee;
  };

  CountHolder* counter;
  void init();
  void MakeCopy();
};


template<typename T>
void RCIPtr<T>::init() {
  if (counter->IsShareable() == false) {
    T* old_value = counter->pointee;
    counter = new CountHolder;
    counter->pointee = new T(*old_value);
  }
  counter->AddReference();
}

template<typename T>
RCIPtr<T>::RCIPtr(T* real_ptr) : counter(new CountHolder) {
  counter->pointee = real_ptr;
  init();
}

template<typename T>
RCIPtr<T>::RCIPtr(const RCIPtr& rhs) : counter(rhs.counter) {
  init();
}

template<typename T>
RCIPtr<T>::~RCIPtr() {
  counter->RemoveReference();
}

template<typename T>
RCIPtr<T>& RCIPtr<T>::operator=(const RCIPtr& rhs) {
  if (counter != rhs.counter) {
    counter->RemoveReference();
    counter = rhs.counter;
    init();
  }
  return *this;
}

template<typename T>
const T* RCIPtr<T>::operator->() const {
  return counter->pointee;
}

template<typename T>
const T& RCIPtr<T>::operator*() const {
  return *(counter->pointee);
}

RCObject::RCObject() : reference_count(0), shareable(true) {}

RCObject::RCObject(const RCObject&) : reference_count(0), shareable(true) {}

RCObject& RCObject::operator=(const RCObject&) {
  return *this;
}

RCObject::~RCObject() {}

void RCObject::AddReference() {
  ++reference_count;
}

void RCObject::RemoveReference() {
  if (--reference_count == 0) {
    delete this;
  }
}

void RCObject::MarkUnshareable() {
  shareable = false;
}

bool RCObject::IsShareable() const {
  return shareable;
}

bool RCObject::IsShared() const {
  return reference_count > 1;
}


class Widget {
 public:
  Widget(int size) : size_(size) {
    std::cout << "Widget::Widget(int size) called.\n";
  }
  Widget(const Widget& rhs) : size_(rhs.size_) {}
  ~Widget() {
    std::cout << "Widget::~Widget() called.\n";
  }
  Widget& operator=(const Widget& rhs) {
    size_ = rhs.size_;
    return *this;
  }
  void DoThis() {
    std::cout << "DoThis(): my size is " << size_ << '\n';
  }
  int ShowThat() const {
    std::cout << "ShowThat(): my size is " << size_ << '\n';
    return size_;
  }

 private:
  int size_;
};

class RCWidget {
 public:
 RCWidget(int size) : value(new Widget(size)) {}
 void DoThis() {
   value->DoThis();
 }
 int ShowThat() const {
   return value->ShowThat();
 }
 private:
  RCIPtr<Widget> value;
};

int main() {
  std::cout << "begin main()\n";
  {
    Widget w(42);
  }

  {
    RCWidget rcw(88);
  }
  std::cout << "end main()\n";
  return 0;
}
