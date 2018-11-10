int getISP(char c)
{
	if (c == '(')
		return 1;
	else if (c == '*' || c == '/' || c == '%' || c == '^')
		return 5;
	else if (c == '+' || c == '-')
		return 3;
	else if (c == ')')
		return 8;
	else
		return 0;
}

int getICP(char c)
{
	if (c == '(')
		return 8;
	else if (c == '*' || c == '/' || c == '%' || c == '^')
		return 4;
	else if (c == '+' || c == '-')
		return 2;
	else if (c == ')')
		return 1;
	else 
		return 0;
}