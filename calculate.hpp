#ifndef _calculate_hpp_
#define _calculate_hpp_

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <stack>
#include <map>
#include <string>
#include <sstream>
#include <vector>

class Calculate
{
public:
	void calculate(std::vector<std::string>);
private:
	void to_postfix(std::string, int);
	bool is_operand(char);
	bool is_operator(char);
	int priority(char);	
	void evaluate(int, int, int);
	void display(int , int);

	std::string m_postfix;
	std::vector<double> m_answers;
};
#endif
