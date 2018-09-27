#include "calculate.hpp"

int main(int argc, char** argv)
{
	std::vector<std::string> s;
	if (argc != 4)
		std::cerr<<"Missing argumnets\n";
	for (int i = 1; i < argc; ++i)
	{
		std::cout << argv[i] << std::endl;
		s.push_back(argv[i]);
	}
	Calculate c;
	c.calculate(s);
}
