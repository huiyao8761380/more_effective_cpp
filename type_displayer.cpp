#include <atomic>
#include <array>
#include <vector>
#include <iostream>
#include <typeinfo>
#include <boost/type_index.hpp>


template<typename T>
void display_type(const T& param)
{
	using std::cout;
	using boost::typeindex::type_id_with_cvr;

	// show T
	cout << "T = 	"
		 << type_id_with_cvr<T>().pretty_name()
		 << '\n';

	// show param's type
	cout << "param = "
		 << type_id_with_cvr<decltype(param)>().pretty_name()
		 << '\n';
}



template<typename T, std::size_t N>
constexpr std::size_t arraySize(T (&array_name)[N]) noexcept
{
	return N;
}

auto create0()
{
	return std::vector<int>(5, 42);
}

auto createInitList()
{
	//return {1, 2, 3};
}


decltype(auto) f1()
{
	int x = 0;

	return x;
}

decltype(auto) f2()
{
	int x = 0;

	return (x);
}

template<typename T>
class TD;

class Widget {
public:
	Widget() : i(0) {std::cout << "call Widget()\n"; }
	Widget(int _i) : i(_i) {std::cout << "call Widget(int)\n"; }
	Widget(int i, bool b) { std::cout << "call Widget(int, bool)\n"; }
	Widget(int i, double d) { std::cout << "call Widget(int, double)\n"; }
	//Widget(std::initializer_list<long double> il) { std::cout << "call Widget(std::initializer_list<long double>)\n"; }
//	Widget(std::initializer_list<bool> il) { std::cout << "call Widget(std::initializer_list<bool>)\n"; }

	Widget(std::initializer_list<std::string> il) { std::cout << "call Widget(std::initializer_list<std::string>)\n"; }

	Widget(const Widget &w) : i(w.i) { std::cout << "call Widget(const Widget &)\n"; }

	operator float() const {std::cout << "call operator float() const\n"; return 42.0; }
private:
	int i;
};

std::vector<Widget> createVec()
{
	std::vector<Widget> res;
	Widget d, d1;
	res.push_back(d);
	res.push_back(d1);
	return res;
}

template<typename T>
void f(const T& param)
{
	using std::cout;
	
	cout << "T = " << typeid(T).name() << '\n';
	cout << "param = " << typeid(param).name() << '\n';
}


int main()
{
	int i0(0);
	int i1 = 0;
	int i2 {0};
	int i3 = {0};
	std::vector<int> ivec {1, 3, 5};
	std::atomic<int> ai0{0};
	std::atomic<int> ai2(0);
	std::atomic<int> ai3 = 0;// error
	double d0 = 1.2, d1 = 2.3;
	//int sum1 {d0 + d1};// error
	int sum2 (d0 + d1);
	int sum3 = d0 + d1;
	
	Widget w1(10);
	Widget w2();// most vexing parse
	Widget w3{};

	Widget w11(10, true);
	Widget w22{10, true};
	Widget w33(10, 5.0);
	Widget w4{10, 5.0};

	Widget w5(w4);
	Widget w6{w4};
	Widget w7(std::move(w4));
	Widget w8{std::move(w4)};
	
	Widget w9({});
	Widget w10 {{}};
	int xx1;
//	auto xx2;// error
	auto xx3 = 0;

	int keyVals[] = {1,2,3};
	std::cout << arraySize(keyVals) << '\n';
	std::array<int, arraySize(keyVals)> mappedVals;
	double d = 2.3;
	int idx1 = d * mappedVals.size();
	auto idx2 = d * mappedVals.size();
	auto idx3 = static_cast<int>(d * mappedVals.size());
	std::cout << idx1 << ' ' << idx2 << ' ' << idx3 << '\n';
	std::vector<int> V;
	auto resetV = [&V](const auto& newValue) { V = newValue; };// c++14
//	resetV({1,2,3});
	auto x1 = 27;
	auto x2(27);
	auto x3 = {27};
	auto x4 {27};
//	auto x5 {1,2,3.0};
	std::cout << f1() << '\n';
	std::cout << f2() << '\n';

	std::cout << "display_type NOT using boost/type_index.hpp" << '\n';
	const auto vw = createVec();
	if (!vw.empty()) {
		f(&vw[0]);
	}	

	
	std::cout << "display_type using boost/type_index.hpp" << '\n';
	if (!vw.empty()) {
		display_type(&vw[0]);
	}	

	const int theAnswer = 42;

	auto x = theAnswer;
	auto y = &theAnswer;

//	TD<decltype(x)> xType;
//	TD<decltype(y)> yType;


	return 0;
}
