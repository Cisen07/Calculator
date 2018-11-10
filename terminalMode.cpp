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
	cout << "������Ҫ�������׺���ʽ (!!������������Ӣ�ĵ�����!!):" << endl;
	getline(cin, midfix);
	postfix = transformToPostfix(midfix);
	cout << "��׺���ʽΪ(����֮���Կո�ָ�): " << postfix << endl;
	cout << "��׺���ʽ����Ľ��Ϊ: " << calculateByMidfix(midfix) << endl;
	cout << "��׺���ʽ������Ϊ: " << calculateByPostfix(postfix) << endl << endl;
}