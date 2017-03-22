#include <iostream>
#include <string>
using namespace std;

#include "LinkQueue.h"
typedef string ElemType;

int main() {
	LinkQueue<ElemType> my_queue;
	my_queue.show_infor();
	cout << endl;

	int i = 1;
	ElemType elem="";
	cout << "--入队测试--" << endl;
	while (elem != "#") {
		cout << "请输入第" << i++ << "个元素（输入‘#’表示结束输入）：";
		cin >> elem;
		if(elem!="#")
			my_queue.append(elem);
	} 
	cout << endl;
	my_queue.show_infor();
	cout << endl;

	cout << "--测试出队--" << endl;
	if (my_queue.is_empty()) {
		cout << "队列为空，不能出队！" << endl;
	}
	else {
		cout << "当前队头元素：" << my_queue.get_first() << endl;
		my_queue.remove();
		cout << "执行出队操作以后：" << endl;
		my_queue.show_infor();
		cout << endl;
	}

	cout << "--清空队列--" << endl;
	my_queue.clear();
	my_queue.show_infor();
	cout << endl;

	system("pause");
	return 0;
}