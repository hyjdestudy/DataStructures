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
	cout << "--��Ӳ���--" << endl;
	while (elem != "#") {
		cout << "�������" << i++ << "��Ԫ�أ����롮#����ʾ�������룩��";
		cin >> elem;
		if(elem!="#")
			my_queue.append(elem);
	} 
	cout << endl;
	my_queue.show_infor();
	cout << endl;

	cout << "--���Գ���--" << endl;
	if (my_queue.is_empty()) {
		cout << "����Ϊ�գ����ܳ��ӣ�" << endl;
	}
	else {
		cout << "��ǰ��ͷԪ�أ�" << my_queue.get_first() << endl;
		my_queue.remove();
		cout << "ִ�г��Ӳ����Ժ�" << endl;
		my_queue.show_infor();
		cout << endl;
	}

	cout << "--��ն���--" << endl;
	my_queue.clear();
	my_queue.show_infor();
	cout << endl;

	system("pause");
	return 0;
}