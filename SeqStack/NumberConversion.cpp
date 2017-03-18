/*利用顺序栈实现数制转换*/

#include <iostream>
using namespace std;

#include  "SeqStack.h"
typedef int ElemType;

//数制转换函数（把十进制数num转换成x进制，要用一个size大小的顺序栈）
void conversion(int num,int x,int size);

int main() {
	int num=0;
	int x = 10;
	int stack_size = 0;

	do {
		cout << "请输入栈的容量：";
		cin >> stack_size;
		cout << "请输入要转换的十进制数：";
		cin >> num;
		cout << "请输入要转换成的数制：";
		cin >> x;
	} while (num<0 || x<0 || stack_size<0);
	cout << endl;
	conversion(num,x,stack_size);
	cout << endl;
	system("pause");
	return 0;
}

//数制转换函数（把十进制数num转换成x进制）
void conversion(int num,int x, int size) {
	SeqStack<ElemType> my_stack(size);
	while (num != 0) {
		my_stack.push(num%x);
		num = num / x;
	}
	cout << "十进制数" << num << "转换成" << x << "进制数为：";
	while (!my_stack.is_empty()) {
		cout << my_stack.get_top();
		my_stack.pop();
	}
	cout << endl;
}