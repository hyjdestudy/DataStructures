#include <iostream>
#include <string>
#include "LinkStack.h"
using namespace std;

typedef char ElemType;

bool check_brackets(string exp);

int main() {
	string exp;
	bool result=false;
	cout << "请输入一个带有括号（( ),[ ],{ }）的表达式："<<endl;
	cin >> exp;

	result=check_brackets(exp);
	if (result) {
		cout << "括号成功匹配！" << endl;
	}
	else {
		cout << "括号不匹配！" << endl;
	}
	cout << endl;
	system("pause");
	return 0;
}

bool check_brackets(string exp) {
	bool flag = true;
	LinkStack<ElemType> my_stack;
	int i = 0;
	ElemType ch;
	while (exp[i] != '\0') {
		if (exp[i] == '(' || exp[i] == '[' || exp[i] == '{') {  //遇到的左括号都进栈
			my_stack.push(exp[i]);
		}

		if (exp[i] == ')' || exp[i] == ']' || exp[i] == '}') {  //遇到右括号，检查右括号是否和栈顶括号匹配
			ch = my_stack.get_top();
			if ( (exp[i] == ')' && ch == '(') || (exp[i] == ']' && ch == '[') || (exp[i] == '}' && ch == '{') ) {  //匹配到()或[]或{}
				my_stack.pop();
			}
			else {
				flag = false;
				break;
			}
		}
		i++;  //继续检查下一个字符
	}

	if (!my_stack.is_empty()) {  //表达式已扫描完，但是栈没弹空，说明有不匹配的左括号
		flag = false;
	}
	return flag;
}