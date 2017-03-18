#include <iostream>
using namespace std;

#include "LinkStack.h"

typedef int ElemType;

int main() {
	//��ʼ��һ����ջ
	LinkStack <ElemType> my_stack;
	my_stack.show_infor();

	//������ջ
	int num = 0;
	ElemType elem;
	do {
		cout << "��ָ��Ԫ�ظ�����";
		cin >> num;
	} while (num<0);
	int i = 0;
	for (i = 0; i < num; i++) {
		cout << "�������" << i + 1 << "��Ԫ�أ�";
		cin >> elem;
		my_stack.push(elem);
	}
	cout << endl;
	my_stack.show_infor();

	//���Գ�ջ
	int num_pop=0;
	cout << "��ָ����Ҫ����Ԫ�صĸ�������ǰջ��ֻ��"<<my_stack.get_length()<<"��Ԫ�أ���";
	cin >> num_pop;
	for (i = 1; i <= num_pop; i++) {
		cout << "������" << i << "��Ԫ�أ�" << my_stack.get_top() << endl;
		my_stack.pop();
	}
	cout << endl;
	my_stack.show_infor();

	cout << "ִ�����ջ����..." << endl;
	my_stack.clear();
	my_stack.show_infor();
	cout << endl;
	system("pause");
	return 0;
}