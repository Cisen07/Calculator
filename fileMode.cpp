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
		int k = 0;	//k����ʹ��һ�в��ڿ�ͷ��endl��Ϊ�˱���һ�����д��󣬲������ɵ�txt�ļ���β��\n
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
			cout << "��" << lines << "����׺���ʽ�ļ������ǣ�" << result << endl;
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
			cout << "��" << lines << "����׺���ʽ�ļ������ǣ�" << result << endl;
		}
		infile.close();
		cout << endl;
	}
}

void modeFile()
{
	cout << "�������ļ���(ע���׺) ->" << endl;
	string file;
	cin >> file;
	readTxt_calculateMidfix_transform(file);
	readTxt_calculatePostfix("postfix.txt");
}