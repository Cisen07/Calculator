#include <string>
#include <iostream>
#include <stack>
#include <cmath>

#include "priority.h"

using namespace std;

bool isOperator(char c)
{
	if (c == '*' || c == '/' || c == '+' || c == '-' || c == '^' || c == '%')
		return true;
	else
		return false;
}

bool isNumber(char c)
{
	if ((c >= '0'&& c <= '9') || c == '.')	//注意这里把'.'也暂时当作数字对待
		return true;
	else
		return false;
}

std::string transformToPostfix(const std::string& midfix)
{
	stack<char> operatorStack;
	string postfix;
	char c;
	for (unsigned int current = 0; current < midfix.length(); current++)
	{
		c = midfix.at(current);
		if (!isNumber(c) && !isOperator(c) && c != '(' && c != ')' && c != ' ')
		{
			cout << "输入的表达式错误1" << endl;
			system("pause");
			exit(0);
		}
		if (c != ' ')				
		{
			if (c == '(' || c == ')')
			{
				if (operatorStack.empty())
				{  
					operatorStack.push(c);
				}
				else
				{	//栈顶优先级高于当前运算符的依次出栈，直到 栈为空 或者 栈顶运算符优先级低于当前运算符
					while (getICP(c) < getISP(operatorStack.top()))
					{
						if (operatorStack.top() != '(')
						{
							postfix.append(1, operatorStack.top());
							postfix.append(1, ' ');
							operatorStack.pop();
						}
						else
						{
							operatorStack.pop();
							if (!operatorStack.empty())
							{
								c = operatorStack.top();
							}
						}
						if (operatorStack.empty())
							break;
					}
					if (getICP(c) == getISP(operatorStack.top()))
					{
						operatorStack.pop();
					}
					else
					{
					operatorStack.push(c);
					}
				}
			}
			else if (isOperator(c))
			{   
				if (current + 1 < midfix.length() && isOperator(midfix.at(current + 1)))	
				{//已扫描的长度小于总长，说明后面还有未扫描的部分；下一位同样是操作符，显然中缀表达式中操作符和操作符不会紧密相连
					cout << "输入的表达式错误2";
					system("pause");
					exit(0);
				}
				if (operatorStack.empty())
				{  
					operatorStack.push(c);
				}
				else
				{	//栈顶优先级高于当前运算符的依次出栈，直到 栈为空 或者 栈顶运算符优先级低于当前运算符
					while (getICP(c) < getISP(operatorStack.top()))
					{
						postfix.append(1, operatorStack.top());
						postfix.append(1, ' ');
						operatorStack.pop();
						if (operatorStack.empty())
							break;
					}
					operatorStack.push(c);
				}
			}
			else  
			{	//c是数字
				postfix.append(1, c);
				if ((current + 1 < midfix.length() && !isNumber(midfix.at(current + 1))) || current + 1 == midfix.length())	//当前数字字符后面有非数字字符，说明该数字扫描完了，加一个分隔符来标记；抑或是扫描完毕，可能栈中还有符号
				{
					postfix.append(1, ' ');	//空格作为数字分隔符 
				}
			}
		}
	}
	while (!operatorStack.empty())
	{//中缀表达式读取完毕后将运算符栈中剩下的运算符拼接到后缀表达式中
		if (operatorStack.top() == '(' || operatorStack.top() == ')')
		{
			cout << "输入的表达式错误3";
			system("pause");
			exit(0);
		}
		postfix.append(1, operatorStack.top());
		postfix.append(1, ' ');
		operatorStack.pop();
	}
	return postfix;
}

double calculateByMidfix(std::string midfix)
{
	stack<double> digitStack;
	stack<double> operatorStack;
	double temp;
	char c, oper;
			
	for (unsigned int i = 0; i < midfix.length(); i++)
	{
		
		c = midfix.at(i);
		if (isNumber(c))
		{
			double digit = c - '0';
			int k = 0;
			while (i + 1 < midfix.length() && isNumber(midfix.at(i + 1)))
			{
				if (midfix.at(i + 1) == '.')
				{
					k++;
				}
				else if ((c >= '0'&& c <= '9') && k == 0)
				{
					digit = digit * 10 + (midfix.at(i + 1) - '0');
				}
				else if (k != 0 && midfix.at(i + 1) != ' ')
				{
					digit = digit + (midfix.at(i + 1) - '0') * pow(10, -1 * k);
					k++;
				}
				i++;
			}
			digitStack.push(digit);
		}
		else if (isOperator(c) || c == '(' || c == ')')
		{
			if (operatorStack.empty())
			{
				operatorStack.push(c);
			}
			else if (getICP(c) > getISP(operatorStack.top()))
			{
				operatorStack.push(c);
			}
			else if (c == ')' && operatorStack.top() == '(')
			{
				operatorStack.pop();
			}
			else if (getICP(c) < getISP(operatorStack.top()))
			{
				while (!operatorStack.empty() && getICP(c) < getISP(operatorStack.top()))
				{
					oper = operatorStack.top();
					operatorStack.pop();
					double a = digitStack.top();
					int a1 = digitStack.top();
					digitStack.pop();
					double b = digitStack.top();
					int b1 = digitStack.top();
					digitStack.pop();
					double temp;
					switch (oper)
					{
					case '+':
						temp = b + a;
						break;
					case '-':
						temp = b - a;	//先弹出的放在表达式右侧
						break;
					case '/':
						if (a ==
							0)
						{
							cout << "除数不得为零";
							system("pause");
							exit(0);
						}
						temp = b / a;
						break;
					case '*':
						temp = b * a;
						break;
					case '%':
						temp = b1 % a1;
						break;
					case '^':
						temp = pow(b, a);
					default:
						break;
					}
					digitStack.push(temp);
				}
				if (operatorStack.empty())
				{
					operatorStack.push(c);
				}
				else if (getICP(c) > getISP(operatorStack.top()))
				{
					operatorStack.push(c);
				}
				else if (c == ')' && operatorStack.top() == '(')
				{
					operatorStack.pop();
				}
			}
			
		}
	}
	while (!operatorStack.empty())
	{
		oper = operatorStack.top();
		operatorStack.pop();
		double a = digitStack.top();
		int a1 = digitStack.top();
		digitStack.pop();
		double b = digitStack.top();
		int b1 = digitStack.top();
		digitStack.pop();
		double temp;
		switch (oper)
		{
		case '+':
			temp = b + a;
			break;
		case '-':
			temp = b - a;	//先弹出的放在表达式右侧
			break;
		case '/':
			if (a ==
				0)
			{
				cout << "除数不得为零";
				system("pause");
				exit(0);
			}
			temp = b / a;
			break;
		case '*':
			temp = b * a;
			break;
		case '%':
			temp = b1 % a1;
			break;
		case '^':
			temp = pow(b, a);
		default:
			break;
		}
		digitStack.push(temp);
	}
	return digitStack.top();
}

double calculateByPostfix(std::string postfix)
{
	stack<double> result;
	char c;
	for (unsigned int i = 0; i < postfix.length(); i++)
	{
		c = postfix.at(i);
		if (isOperator(c))
		{
			double a = result.top();
			int a1 = result.top();
			result.pop();
			double b = result.top();
			int b1 = result.top();
			result.pop();
			double temp;
			switch (c)
			{
			case '+':
				temp = b + a;
				break;
			case '-':
				temp = b - a;	//先弹出的放在表达式右侧
				break;
			case '/':
				if (a == 0)
				{
					cout << "除数不得为零";
					system("pause");
					exit(0);
				}
				temp = b / a;
				break;
			case '*':
				temp = b * a;
				break;
			case '%':
				temp = b1 % a1;
				break;
			case '^':
				temp = pow(b, a);
			default:
				break;
			}
			result.push(temp);
		}
		else if (isNumber(c))
		{
			double num = c - '0';
			int k = 0;
			while (isNumber(postfix.at(i + 1)))
			{
				if (postfix.at(i + 1) == '.')
				{
					k = 1;
				}
				else if ((c >= '0'&& c <= '9') && k == 0)
				{
					num = num * 10 + (postfix.at(i + 1) - '0');
				}
				else if (k != 0 && postfix.at(i + 1) != ' ')
				{
					num = num + (postfix.at(i + 1) - '0') * pow(10, -1 * k);
					k++;
				}	
				i++;
			}
			result.push(num);
		}
	}
	return result.top();
}