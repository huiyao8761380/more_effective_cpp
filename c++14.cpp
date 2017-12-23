#include <tuple>
#include <iostream>
#include <array>
#include <utility>
#include <vector>

// Convert array into a tuple
template<typename Array, std::size_t... I>
decltype(auto) a2t_impl(const Array& a, std::index_sequence<I...>)
{
    return std::make_tuple(a[I]...);
}
 
template<typename T, std::size_t N, typename Indices = std::make_index_sequence<N>>
decltype(auto) a2t(const std::array<T, N>& a)
{
    return a2t_impl(a, Indices{});
}
 
// pretty-print a tuple
 
template<class Ch, class Tr, class Tuple, std::size_t... Is>
void print_tuple_impl(std::basic_ostream<Ch,Tr>& os,
                      const Tuple & t,
                      std::index_sequence<Is...>)
{
    ((os << (Is == 0? "" : ", ") << std::get<Is>(t)), ...);
}
 
template<class Ch, class Tr, class... Args>
decltype(auto) operator<<(std::basic_ostream<Ch, Tr>& os,
                          const std::tuple<Args...>& t)
{
    os << "(";
    print_tuple_impl(os, t, std::index_sequence_for<Args...>{});
    return os << ")";
}
 
int main()
{
    std::array<int, 4> array {{1,2,3,4}};
	std::vector<int> ivec;


    // convert an array into a tuple
    auto tuple = a2t(array);
    static_assert(std::is_same<decltype(tuple),
                               std::tuple<int, int, int, int>>::value, "");
 
    // print it to cout
    std::cout << tuple << '\n';
}
