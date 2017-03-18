#include <iostream>
#include <string>
#include "LinkStack.h"
using namespace std;

typedef char ElemType;

bool check_brackets(string exp);

int main() {
	string exp;
	bool result=false;
	cout << "������һ���������ţ�( ),[ ],{ }���ı��ʽ��"<<endl;
	cin >> exp;

	result=check_brackets(exp);
	if (result) {
		cout << "���ųɹ�ƥ�䣡" << endl;
	}
	else {
		cout << "���Ų�ƥ�䣡" << endl;
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
		if (exp[i] == '(' || exp[i] == '[' || exp[i] == '{') {  //�����������Ŷ���ջ
			my_stack.push(exp[i]);
		}

		else if (exp[i] == ')' || exp[i] == ']' || exp[i] == '}') {  //���������ţ�����������Ƿ��ջ������ƥ��
			if (!my_stack.is_empty()) {  //һ��ע�ⵯ��֮ǰ���ջ�Ƿ�Ϊ��
				ch = my_stack.get_top();
				if ((exp[i] == ')' && ch == '(') || (exp[i] == ']' && ch == '[') || (exp[i] == '}' && ch == '{')) {  //ƥ�䵽()��[]��{}
					my_stack.pop();
				}
				else {
					flag = false;
					cout << "��һ����ƥ��������ų����ڱ��ʽ�ĵ�" << i+1 << "��λ�ã�"<<endl;
					break;
				}
			}	
			else {  //ջ�Ѿ������ˣ�����������������
				flag = false;
				cout << "��һ����ƥ��������ų����ڱ��ʽ�ĵ�" << i + 1 << "��λ�ã�" << endl;
				break;
			}
		}
		i++;  //���������һ���ַ�
	}

	if (exp[i] == '\0' && !my_stack.is_empty()) {  //���ʽ��ɨ���꣬����ջû���գ�˵���в�ƥ���������
		flag = false;
		cout << "�ж���������ţ�" << endl;
	}
	return flag;
}