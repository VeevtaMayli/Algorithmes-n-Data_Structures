/*
22. В строке текстового файла  задано  выражение  из  целых
чисел и операций '+', '-', '*', '/', '^'.  Порядок  вычислений
определяется приоритетом операций и круглыми скобками. Возможен
одноместный минус в начале  выражения  или  после  открывающей
скобки. Преобразовать выражение в постфиксную  форму (алгоритм
Дейкстры) и вычислить его значение. Показать этапы  выполнения
(11).
Матвеев Илья
ИПС-2017
*/

#include "pch.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

template <typename valueType>
struct stack
{
	valueType value;
	struct stack *next;
};

template <typename valueType>
void push(stack<valueType> *&ptr, valueType elem)
{
	stack<valueType> *temp = new stack<valueType>;
	temp->value = elem;
	temp->next = ptr;
	ptr = temp;
}

template <typename valueType>
void pop(stack<valueType> *&ptr)
{
	stack<valueType> *temp = ptr;
	ptr = (*ptr).next;
	delete(temp);
}

int getOperationPriority(char operation)
{
	switch (operation)
	{
	case ')':
		return 1;
	case '(':
		return 2;
	case '+':
	case '-':
		return 3;
	case '*':
	case '/':
		return 4;
	case '^':
		return 5;
	case '~':
		return 6;
	default:
		return 0;
	}
}

float calculatePN(std::string exp)
{
	float result = 0;
	stack<float> *top = NULL;

	for (int i = 0; i < exp.length(); i++)
	{
		if (isdigit(exp[i]))
		{
			std::string number;

			while (exp[i] != ' ' && !getOperationPriority(exp[i]))
			{
				number += exp[i];
				i++;
				if (exp[i] == exp.length())
				{
					break;
				}
			}
			push(top, stof(number));
			i--;
		}
		else if (getOperationPriority(exp[i]))
		{
			float a = top->value;
			pop(top);

			float b = 0;
			if (exp[i] != '~')
			{
				b = top->value;
				pop(top);
			}

			switch (exp[i])
			{
			case '~':
				result = -a;
				break;
			case '+':
				result = b + a;
				break;
			case '-':
				result = b - a;
				break;
			case '*':
				result = b * a;
				break;
			case '/':
				result = b / a;
				break;
			case '^':
				result = pow(b, a);
				break;
			default:
				break;
			}
			push(top, result);
		}
	}
	return top->value;
}

int main(int argc, char* argv[])
{
	stack<char> *top = NULL;
	char lexem;
	std::string result = "";

	if (argc != 2)
	{
		std::cout << "Incorrect arguments count\n"
			<< "Usage: lw1_22.exe <input file>\n";
		return 1;
	}

	std::ifstream input((std::string) argv[1]);

	if (!input.is_open())
	{
		std::cout << "Failed to open " << argv[1] << " for reading\n";
		return 1;
	}

	if (input.eof())
	{
		std::cout << "Empty input file\n";
		input.close();
		return 1;
	}

	while (!input.eof())
	{
		lexem = input.get();

		if (lexem != ' ' && lexem != EOF)
		{
			std::cout << lexem << "|";

			if (isdigit(lexem))
			{
				result += lexem;
			}
			else if (result != "" && lexem != '(')
			{
				result += ' ';
			}
			
			if (getOperationPriority(lexem)) {
				if (lexem == '-' && result == "")
				{
					push(top, '~');
				}
				else if (lexem == '(')
				{
					push(top, lexem);
					if (input.peek() == '-')
					{
						lexem = input.get();
						push(top, '~');
					}
				}
				else if (lexem == ')')
				{
					char tempLexem = top->value;
					pop(top);

					while (tempLexem != '(')
					{
						result += tempLexem;
						if (top->value != '(')
						{
							result += ' ';
						}
						tempLexem = top->value;
						pop(top);
					}
				}
				else
				{
					if (top != NULL)
					{
						while (top != NULL && getOperationPriority(lexem) <= getOperationPriority(top->value) && lexem != '^')
						{
							std::cout << top->value;
							result += top->value;
							result += ' ';
							pop(top);
						}
					}
					push(top, lexem);
				}
			}
			
			stack<char>* ptr = top;
			std::string tempStr = "";
			while (ptr != NULL) {
				 tempStr += ptr->value;
				ptr = ptr->next;
			}
			std::reverse(tempStr.begin(), tempStr.end());
			std::cout << tempStr << std::endl;
		}
	}

	if (top != NULL)
	{
		while (top != NULL)
		{
			result += ' ';
			result += top->value;
			pop(top);
		}
	}

	std::cout << result << std::endl;
	std::cout << "Result: " << calculatePN(result) << std::endl;
	return 0;
}
