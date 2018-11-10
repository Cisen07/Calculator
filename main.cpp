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
	cout << "	*" << "	ʵ��һ��������������	" << "*" << endl;
	cout << "	*" << "	֧��+ - * / () ^ %	" << "*" << endl;
	cout << "	*" << "	֧�ָ���������		" << "*" << endl;
	cout << "	*********************************" << endl << endl;
	while (1)
	{
		cout << "*************************************************************************************************" << endl;
		cout << "	ѡ���������ģʽ(��������)��" << endl << "	[1]�ն�	[2]�ļ� [3]�˳�: ";
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