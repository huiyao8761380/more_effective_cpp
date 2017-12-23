#include <iostream>
#include <mutex>
#include <memory>
void f(int i)
{
	std::cout << "call f(int)\n";
}

void f(bool b)
{
	std::cout << "call f(bool)\n";
}

void f(void * ptr)
{
	std::cout << "call f(void *)\n";
}

class widget {

};

int f1(std::shared_ptr<widget> spw) 
{
	std::cout << "call f1(std::shared_ptr<widget> spw))\n";
	return 0;
}

double f2(std::unique_ptr<widget> upw) 
{
	std::cout << "call f2(std::unique_ptr<widget> upw))\n";
	return 1.0;
}

bool f3(widget* pw)
{
	std::cout << "call f3(widget* pw)\n";
	return false;
}

template<typename FuncType,
		 typename MuxType,
		 typename PtrType>
decltype(auto) lockAndCall(FuncType func,
						   MuxType& mutex,
						   PtrType ptr)
{
	using MuxGuard = std::lock_guard<MuxType>;

	MuxGuard g(mutex);
	return func(ptr);
}

int main()
{
	std::mutex f1m, f2m, f3m;
	
	auto result1 = lockAndCall(f1, f1m, 0);//error
	auto result2 = lockAndCall(f2, f2m, NULL);//error
	auto result3 = lockAndCall(f3, f3m, nullptr);


	f(0);
	//f(NULL);// error
	f(nullptr);


	return 0;
}
