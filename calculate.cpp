#include "calculate.hpp"
#include <algorithm>

bool Calculate::is_operand(char c)
{
	return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '.';
}

bool Calculate::is_operator(char c)
{
	return c == '+' || '-' || '*' ||  '/'; 
}

int Calculate::priority(char c)
{
		switch (c)
		{
			case '+':
			case '-':
				return 1;
			case '*':
			case '/':
				return 2;
			default:
				assert(false);
		}
}

void Calculate::calculate(std::vector<std::string> ob)
{
	if (ob.size() != 3)
	{
		std::cout << "wrong input" << std::endl;
		return;
	}
	else
	{
		std::string s1 = ob[0];
		int index = 0;
		for (int i = 0; i < s1.size(); ++i)
		{	
			if (s1[i] == '[' && s1[i + 1] == 'x' && s1[i + 2] == ']')
				if (s1[i + 3] == '=')
				{
					index = i + 4;
					break;
				}	
				else
					std::cout <<"Function is wrong" << std::endl;
		} 
		to_postfix(s1, index);
		
		std::string s2 = ob[1];
		std::stringstream temp;

		for (int i = 0; i < s2.size(); ++i)
		{
			if (s2[i] == '[')
			{
				++i;
				while (i< s2.size() && s2[i] != '.')
				{
					temp << s2[i];
					++i; 		
				}	
				break;
			}
		}
		std::string t = temp.str();	
		double a = atof(t.c_str());
		
		std::stringstream temp2;
		for (int i = s2.size() - 1; i > 0; --i)
		{
			if (s2[i] == ']')
			{
				--i; 
				while ( s2[i] != '.' )
				{
					temp2 << s2[i];
					--i;
				}
				break;
			}
		}	

		t.clear();	
		t = temp2.str();
		std::reverse(t.begin(), t.end());	
		double b = atof(t.c_str());
		double l = atof(ob[2].c_str());
		evaluate(a,b,l); 
		display(a,l); 
	}	
}

void Calculate::to_postfix(std::string input, int index)
{
	std::stack<char> stack;
	std::stringstream output;
	
	for (int i = index; i < input.size(); ++i)
	{
		if (input[i] == '[')
		{
			stack.push(input[i]);
			continue;
		}
		if (is_operand(input[i]))
		{
			output << input[i];
			continue;
		}
		if (input[i] == ']')
		{
			while (!stack.empty() && stack.top() != '[')
			{
				output << stack.top();
				stack.pop();
			}
			assert(stack.top() == '[');
			stack.pop();
			continue;
		}
		if (is_operator(input[i]))
		{
			assert(i != 0);
			while (!stack.empty() && stack.top() != '[' && priority(stack.top()) > priority( input[i]))
			{
				output << stack.top();
				stack.pop();
			}
			output << ' ';
			stack.push(input[i]);
		}
	} // end for
	
	while (!stack.empty())
	{
		output << stack.top();
		stack.pop();
	}

	m_postfix = output.str();
} 

void Calculate::evaluate(int a, int b, int l)
{
	std::stack<double> stack;
	int j = a;
	for (; j <= b; ++j)
	{
		for (int i = 0; i < m_postfix.size(); ++i)
		{ 
			if (m_postfix[i] == ' ')
			{
				continue;
			}
			if (is_operand(m_postfix[i]))
			{
				std::stringstream temp;

				while (i < m_postfix.size() && is_operand(m_postfix[i]))
				{
					temp << m_postfix[i];
					++i;
				} // end while 
	
				if (temp.str() == "x")
				{				
					stack.push(j);
				}
				else
				{
					std::string t = temp.str();
					stack.push(atof(t.c_str()));
				}
				--i;		
				continue;
			} 
			if (is_operator(m_postfix[i]))
			{
				double a = stack.top(); 
				stack.pop();
				double b = stack.top(); 
				stack.pop();

				switch (m_postfix[i])
				{
				case '+':
					stack.push(a + b);
					break;
				case '*' :
					stack.push(a * b);
					break;
				case '-':
					stack.push(b - a);
					break;
				case '/':
					stack.push(b / a);
					break;
				}
			}
		} 
		m_answers.push_back(stack.top());
		stack.pop();
	} 
} 

void Calculate::display(int x, int l)
{
	std::cout <<"x  |  y" << std::endl;
	std::cout <<"-------" << std::endl;

	for (int i = 0; i < m_answers.size(); ++i)
	{
		std::cout << x << " | " << m_answers[i] << std::endl;
		x += l;
	}
}

