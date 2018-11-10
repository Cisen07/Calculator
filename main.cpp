#include <string>
#include <iostream>
#include <stack>

#include "transition.h"
#include "terminalMode.h"
#include "fileMode.h"

using namespace std;

int main()
{
	char mode;
	cout << "	*********************************" << endl;
	cout << "	*" << "				" << "*" << endl;
	cout << "	*" << "	实验一（算术计算器）	" << "*" << endl;
	cout << "	*" << "	支持+ - * / () ^ %	" << "*" << endl;
	cout << "	*" << "	支持浮点数运算		" << "*" << endl;
	cout << "	*********************************" << endl << endl;
	while (1)
	{
		cout << "*************************************************************************************************" << endl;
		cout << "	选择计算器的模式(输入数字)：" << endl << "	[1]终端	[2]文件 [3]退出: ";
		cin >> mode;

		switch (mode)
		{
		case '1':
			modeTerminal();
			break;
		case '2':
			modeFile();
			break;
		case '3':
			return 0;
		default:
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
	}

	system("pause");

	return 0;
}