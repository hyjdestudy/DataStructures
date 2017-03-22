/*
循环队列
规定：
1.当rear==front时，队列为空；
2.当front==(rear+1)%size时，队列为满（即队尾和队头差一个元素）
*/
#include <iostream>
using namespace std;
#include "SeqQueue.h"
#define ElemType int

int main() {
	int size = 0;
	do {
		cout << "请输入队列的大小：";
		cin >> size;
	} while (size<=0);
	SeqQueue<ElemType> my_queue(size);	
	my_queue.show_infor();
	cout << endl;

	//添加元素
	int i = 0;
	for (i = 0; i < size-1; i++) {
		my_queue.append(i);
	}
	my_queue.show_infor();
	cout << endl;

	cout << "--测试扩展空间--" << endl;
	cout << "请输入第" << my_queue.get_length()+1 << "个元素：";
	cin >> i;
	my_queue.append(i);
	my_queue.show_infor();
	cout << endl;

	cout << "--测试出队操作--" << endl;
	ElemType v = my_queue.get_first();
	my_queue.remove();
	cout << "出队元素为：" << v << endl;
	my_queue.show_infor();
	cout << endl;

	cout << "--清空队列--" << endl;
	my_queue.clear();
	my_queue.show_infor();
	cout << endl;
	system("pause");
	return 0;
}