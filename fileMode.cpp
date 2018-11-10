#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "transition.h"

using namespace std;

void readTxt_calculateMidfix_transform(std::string file)
{
	char buf[1024];               
	string message;
	ifstream infile;
	infile.open(file);
	if (infile.is_open())         
	{
		ofstream out("postfix.txt");
		int k = 0;	//k用于使第一行不在开头加endl；为了避免一个运行错误，不让生成的txt文件结尾是\n
		int lines = 0;
		while (infile.good() && !infile.eof())
		{
			if (k == 1 && out.is_open())
				out << endl;
			k = 1;
			lines++;
			memset(buf, 0, 1024);
			infile.getline(buf, 1024);
			message = buf;
			double result = calculateByMidfix(message);
			cout << "第" << lines << "个中缀表达式的计算结果是：" << result << endl;
			string postfix;
			if (out.is_open())
			{
				postfix = transformToPostfix(message);
				out << postfix;
			}
		}
		cout << endl;
		out.close();
		infile.close();
	}
}

void readTxt_calculatePostfix(std::string file)
{
	char buf[1024];               
	string message;
	ifstream infile;
	infile.open(file);
	if (infile.is_open())          
	{
		int lines = 0;
		while (infile.good() && !infile.eof())
		{
			lines++;
			memset(buf, 0, 1024);
			infile.getline(buf, 1024);
			message = buf;
			double result = calculateByPostfix(message);
			cout << "第" << lines << "个后缀表达式的计算结果是：" << result << endl;
		}
		infile.close();
		cout << endl;
	}
}

void modeFile()
{
	cout << "请输入文件名(注意后缀) ->" << endl;
	string file;
	cin >> file;
	readTxt_calculateMidfix_transform(file);
	readTxt_calculatePostfix("postfix.txt");
}