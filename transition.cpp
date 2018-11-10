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
	if ((c >= '0'&& c <= '9') || c == '.')	//ע�������'.'Ҳ��ʱ�������ֶԴ�
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
			cout << "����ı��ʽ����1" << endl;
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
				{	//ջ�����ȼ����ڵ�ǰ����������γ�ջ��ֱ�� ջΪ�� ���� ջ����������ȼ����ڵ�ǰ�����
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
				{//��ɨ��ĳ���С���ܳ���˵�����滹��δɨ��Ĳ��֣���һλͬ���ǲ���������Ȼ��׺���ʽ�в������Ͳ����������������
					cout << "����ı��ʽ����2";
					system("pause");
					exit(0);
				}
				if (operatorStack.empty())
				{  
					operatorStack.push(c);
				}
				else
				{	//ջ�����ȼ����ڵ�ǰ����������γ�ջ��ֱ�� ջΪ�� ���� ջ����������ȼ����ڵ�ǰ�����
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
			{	//c������
				postfix.append(1, c);
				if ((current + 1 < midfix.length() && !isNumber(midfix.at(current + 1))) || current + 1 == midfix.length())	//��ǰ�����ַ������з������ַ���˵��������ɨ�����ˣ���һ���ָ�������ǣ��ֻ���ɨ����ϣ�����ջ�л��з���
				{
					postfix.append(1, ' ');	//�ո���Ϊ���ַָ��� 
				}
			}
		}
	}
	while (!operatorStack.empty())
	{//��׺���ʽ��ȡ��Ϻ������ջ��ʣ�µ������ƴ�ӵ���׺���ʽ��
		if (operatorStack.top() == '(' || operatorStack.top() == ')')
		{
			cout << "����ı��ʽ����3";
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
						temp = b - a;	//�ȵ����ķ��ڱ��ʽ�Ҳ�
						break;
					case '/':
						if (a ==
							0)
						{
							cout << "��������Ϊ��";
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
			temp = b - a;	//�ȵ����ķ��ڱ��ʽ�Ҳ�
			break;
		case '/':
			if (a ==
				0)
			{
				cout << "��������Ϊ��";
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
				temp = b - a;	//�ȵ����ķ��ڱ��ʽ�Ҳ�
				break;
			case '/':
				if (a == 0)
				{
					cout << "��������Ϊ��";
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