#ifndef _postfix_hpp_
#define _postfix_hpp

#include <fstream>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <stack>
#include <map>
#include <string>
#include <sstream>
#include <vector>

class Postfix
{
public:
	
	std::string to_postfix(std::fstream&);
	double evaluate();	
private:
	bool is_operand(char);
	bool is_operator(char);
	int priority(char);	
	bool is_map(std::string);

	std::string m_postfix;
	std::map<std::string, double> m_map;
};
#endif
