#pragma once
bool isOperator(char c);
bool isNumber(char c);
std::string transformToPostfix(const std::string& midfix);
double calculateByMidfix(std::string midfix);
double calculateByPostfix(std::string postfix);
void modeTerminal();