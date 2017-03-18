/*����˳��ջʵ������ת��*/

#include <iostream>
using namespace std;

#include  "SeqStack.h"
typedef int ElemType;

//����ת����������ʮ������numת����x���ƣ�Ҫ��һ��size��С��˳��ջ��
void conversion(int num,int x,int size);

int main() {
	int num=0;
	int x = 10;
	int stack_size = 0;

	do {
		cout << "������ջ��������";
		cin >> stack_size;
		cout << "������Ҫת����ʮ��������";
		cin >> num;
		cout << "������Ҫת���ɵ����ƣ�";
		cin >> x;
	} while (num<0 || x<0 || stack_size<0);
	cout << endl;
	conversion(num,x,stack_size);
	cout << endl;
	system("pause");
	return 0;
}

//����ת����������ʮ������numת����x���ƣ�
void conversion(int num,int x, int size) {
	SeqStack<ElemType> my_stack(size);
	while (num != 0) {
		my_stack.push(num%x);
		num = num / x;
	}
	cout << "ʮ������" << num << "ת����" << x << "������Ϊ��";
	while (!my_stack.is_empty()) {
		cout << my_stack.get_top();
		my_stack.pop();
	}
	cout << endl;
}