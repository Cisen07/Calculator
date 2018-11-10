#include <string>
#include <iostream>
#include <stack>
#include <cmath>

#include "transition.h"

using namespace std;

void modeTerminal()
{
	cin.ignore();
	stack<char> operatorStack;
	string midfix, postfix;
	cout << "请输入要计算的中缀表达式 (!!如用括号请用英文的括号!!):" << endl;
	getline(cin, midfix);
	postfix = transformToPostfix(midfix);
	cout << "后缀表达式为(数字之间以空格分割): " << postfix << endl;
	cout << "中缀表达式计算的结果为: " << calculateByMidfix(midfix) << endl;
	cout << "后缀表达式计算结果为: " << calculateByPostfix(postfix) << endl << endl;
}