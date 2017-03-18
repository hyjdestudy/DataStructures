#include <iostream>
using namespace std;

#include "SeqStack.h"
typedef int ElemType;

int main() {
	int choice = 0;  //接收用户选择
	int stack_size = 0;
	int stack_length = 0;
	do {
		cout << "请输入栈的大小：";
		cin >> stack_size;
	} while (stack_size<0);
	SeqStack<ElemType> my_stack(stack_size);

	//添加元素
	int i = 1;
	int user_input = 0;
	while (i <= stack_size) {
		cout << "请输入第" << i << "个元素：";
		cin >> user_input;
		my_stack.push(user_input);
		i++;
	}
	my_stack.show_infor();
	cout << endl;
	
	cout << "测试扩展栈空间，请输入第" << my_stack.get_length() + 1 << "个数据：" << endl;
	cin >> user_input;
	my_stack.push(user_input);
	my_stack.show_infor();
	cout << endl;
	
	int top_elem = my_stack.get_top();
	cout << "取栈顶元素：" << top_elem << endl;
	cout << endl;

	cout << "元素从栈中弹出：" << endl;
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

	cout << "测试清空栈空间，请输入1个数据：" << endl;
	cin >> user_input;
	my_stack.push(user_input);
	my_stack.show_infor();
	cout << "正在执行清空栈操作..." << endl;
	my_stack.clear();	
	my_stack.show_infor();
	cout << endl;
	system("pause");
	return 0;
}