#include <string>
#include <iostream>
#include <optional>
#include <algorithm>
#include <iterator>
// optional can be used as the return type of a factory that may fail
std::optional<std::string> create(bool b) {
    if (b)
        return "Godzilla";
    return {};
}
 
int main()
{
	std::string str {"whoami"};
	std::copy(str.begin(), str.end(), std::ostream_iterator<std::string>(std::cout, "->"));
    std::cout << "create(false) returned "
              << create(false).value_or("empty") << '\n';
 
    // optional-returning factory functions are usable as conditions of while and if
    if (auto str = create(true)) {
        std::cout << "create(true) returned " << *str << '\n';
    }
}
