#include <iostream>
using namespace std;

#include "LinkStack.h"

typedef int ElemType;

int main() {
	//初始化一个链栈
	LinkStack <ElemType> my_stack;
	my_stack.show_infor();

	//测试入栈
	int num = 0;
	ElemType elem;
	do {
		cout << "请指定元素个数：";
		cin >> num;
	} while (num<0);
	int i = 0;
	for (i = 0; i < num; i++) {
		cout << "请输入第" << i + 1 << "个元素：";
		cin >> elem;
		my_stack.push(elem);
	}
	cout << endl;
	my_stack.show_infor();

	//测试出栈
	int num_pop=0;
	cout << "请指定您要弹出元素的个数（当前栈中只有"<<my_stack.get_length()<<"个元素）：";
	cin >> num_pop;
	for (i = 1; i <= num_pop; i++) {
		cout << "弹出第" << i << "个元素：" << my_stack.get_top() << endl;
		my_stack.pop();
	}
	cout << endl;
	my_stack.show_infor();

	cout << "执行清空栈操作..." << endl;
	my_stack.clear();
	my_stack.show_infor();
	cout << endl;
	system("pause");
	return 0;
}