#include "postfix.hpp"

bool Postfix::is_operand(char c)
{
	return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '.';
}

bool Postfix::is_operator(char c)
{
	return c == '+' || '-' || '*' ||  '/'; 
}

int Postfix::priority(char c)
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

bool Postfix::is_map(std::string s)
{
	return m_map.find(s) != m_map.end();
}

std::string Postfix::to_postfix(std::fstream& file)
{
	std::stack<char> stack;
	std::stringstream output;
	std::string input;

	if (file.is_open())
	{
		while (file >> input)
		{
			int index = -1;
			for (int i = 0; i < input.size(); ++i)
			{
				if (input[i] == '=')
				{
					index = i;
					break;
				}
			}
			if (index != -1)
			{
				std::stringstream temp1;
				std::stringstream temp2;
				int i = 0;
				for (; i < index; ++i)
				{
					temp1 << input[i];
				}
				++i;
				for (; i < input.size(); ++i)
				{
					temp2 << input[i];
				}
				std:: string temp = temp2.str();
				m_map[temp1.str()] = atof(temp.c_str());
			}
			else 
			{
				for (int i = 0; i < input.size(); ++i)
				{
					if (input[i] == '(')
					{
						stack.push(input[i]);
						continue;
					}
					if (is_operand(input[i]))
					{
						output << input[i];
						continue;
					}
					if (input[i] == ')')
					{
						while (!stack.empty() && stack.top() != '(')
						{
							output << stack.top();
							stack.pop();
						}
						assert(stack.top() == '(');
						stack.pop();
						continue;
					}
					if (is_operator(input[i]))
					{
						assert(i != 0);
						while (!stack.empty() && stack.top() != '(' && priority(stack.top()) > priority( input[i]))
						{
							output << stack.top();
							stack.pop();
						}
						output << ' ';
						stack.push(input[i]);
					}
				} // end for
			} // end else
		} // end while
		file.close();
	} // end if
	
	while (!stack.empty())
	{
		output << stack.top();
		stack.pop();
	}

	m_postfix = output.str();
	return m_postfix;
} // end to_postfix

double Postfix::evaluate()
{
	std::stack<double> stack;
	
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
	
			if (is_map(temp.str()))
			{				
				stack.push(m_map[temp.str()]);
			}
			else
			{
				std:: string t = temp.str();
				stack.push(atof(t.c_str()));
			}
			--i;
			continue;
		} // end if
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
		} // end if
	} //end for

	return stack.top();
} // end evaluate
