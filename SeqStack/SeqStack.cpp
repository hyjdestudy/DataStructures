#include <iostream>
using namespace std;

#include "SeqStack.h"
typedef int ElemType;

int main() {
	int choice = 0;  //�����û�ѡ��
	int stack_size = 0;
	int stack_length = 0;
	do {
		cout << "������ջ�Ĵ�С��";
		cin >> stack_size;
	} while (stack_size<0);
	SeqStack<ElemType> my_stack(stack_size);

	//���Ԫ��
	int i = 1;
	int user_input = 0;
	while (i <= stack_size) {
		cout << "�������" << i << "��Ԫ�أ�";
		cin >> user_input;
		my_stack.push(user_input);
		i++;
	}
	my_stack.show_infor();
	cout << endl;
	
	cout << "������չջ�ռ䣬�������" << my_stack.get_length() + 1 << "�����ݣ�" << endl;
	cin >> user_input;
	my_stack.push(user_input);
	my_stack.show_infor();
	cout << endl;
	
	int top_elem = my_stack.get_top();
	cout << "ȡջ��Ԫ�أ�" << top_elem << endl;
	cout << endl;

	cout << "Ԫ�ش�ջ�е�����" << endl;
	int j = 1;
	while (!my_stack.is_empty()) {
		cout << my_stack.get_top() << " ";
		my_stack.pop();
		if (j % 5 == 0) {
			cout << endl;
		}
		j++;
	}
	cout << endl<<endl;

	cout << "�������ջ�ռ䣬������1�����ݣ�" << endl;
	cin >> user_input;
	my_stack.push(user_input);
	my_stack.show_infor();
	cout << "����ִ�����ջ����..." << endl;
	my_stack.clear();	
	my_stack.show_infor();
	cout << endl;
	system("pause");
	return 0;
}