#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
	std::string s {"hello"};
	std::cout << s << '\n';
	std::cout << *s.begin() << ' '
			  << *s.cbegin() << ' '
		  	  << *s.crbegin() << '\n';	  
	const std::vector<int> ivec { 1, 2, 3, 4 };
	std::cout << *ivec.begin() << ' '
			  << *ivec.cbegin() << ' '
			  << *ivec.crbegin() << ' '
			  << *ivec.rbegin() << '\n';
	
	return 0;
}
