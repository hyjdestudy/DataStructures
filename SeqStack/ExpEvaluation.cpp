#include <iostream>
#include "SeqStack.h"  //使用顺序栈来做操作符栈、操作数栈
#include "exp_evaluation_fun.h"  //功能函数头文件
using namespace std;

#define MAX_EXPLENGTH 100  //定义表达式最长为100个字符

int main() {
	char *exp;  //存储用户输入的表达式
	exp = new char[MAX_EXPLENGTH];
	double result = 0;  //存储运算结果
	int i = 0;  //逐个字符接收用户的输入
	cout << "请输入一个正确的四则运算表达式（运算数为正整数，以等号结尾）：" << endl;	
	cin >> exp[i];
	while (exp[i] != '=') {
		cin >> exp[++i];
	}
	if (compute_exp(exp, result)) {
		cout << "计算结果为：" << result << endl;
	}
	else {
		cout << "程序错误！" << endl;
	}
	system("pause");
	return 0;
}

