/*
ѭ������
�涨��
1.��rear==frontʱ������Ϊ�գ�
2.��front==(rear+1)%sizeʱ������Ϊ��������β�Ͷ�ͷ��һ��Ԫ�أ�
*/
#include <iostream>
using namespace std;
#include "SeqQueue.h"
#define ElemType int

int main() {
	int size = 0;
	do {
		cout << "��������еĴ�С��";
		cin >> size;
	} while (size<=0);
	SeqQueue<ElemType> my_queue(size);	
	my_queue.show_infor();
	cout << endl;

	//���Ԫ��
	int i = 0;
	for (i = 0; i < size-1; i++) {
		my_queue.append(i);
	}
	my_queue.show_infor();
	cout << endl;

	cout << "--������չ�ռ�--" << endl;
	cout << "�������" << my_queue.get_length()+1 << "��Ԫ�أ�";
	cin >> i;
	my_queue.append(i);
	my_queue.show_infor();
	cout << endl;

	cout << "--���Գ��Ӳ���--" << endl;
	ElemType v = my_queue.get_first();
	my_queue.remove();
	cout << "����Ԫ��Ϊ��" << v << endl;
	my_queue.show_infor();
	cout << endl;

	cout << "--��ն���--" << endl;
	my_queue.clear();
	my_queue.show_infor();
	cout << endl;
	system("pause");
	return 0;
}