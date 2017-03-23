#include <iostream>
using namespace std;
#include "SeqQueue.h"

//�������Ԫ��
struct Dancer {
	char name[20];
	char gender;  //�Ա�'M'��ʾ�У�'F'��ʾŮ
};

typedef Dancer ElemType;

int main() {
	SeqQueue<ElemType> male_queue(50), female_queue(50);  //����������Ů����
	Dancer d;
	cout << "�������������ߵ��������Ա�M/F�����Կո�ָ����ԡ�# #��������" << endl;
	cin >> d.name >> d.gender;
	while (d.gender != '#') {
		if (d.gender == 'M' || d.gender == 'm') {
			male_queue.append(d);
		}
		else if (d.gender == 'F' || d.gender == 'f') {
			female_queue.append(d);
		}
		else {
			cout << "�Ա�������������������Ա�";
			cin >> d.gender;
			continue;
		}
		cin >> d.name >> d.gender;
	}
	cout << endl;
	cout << "--�����Խ��--" << endl;
	while (!male_queue.is_empty() && !female_queue.is_empty()) {
		cout << "�з���";
		d = male_queue.get_first();
		male_queue.remove();
		cout << d.name<<"\t";
		cout << "Ů����";
		d = female_queue.get_first();
		female_queue.remove();
		cout << d.name << endl;
	}
	cout << endl;
	if (!male_queue.is_empty()) {
		cout << "����" << male_queue.get_length() << "λ�������ڵȴ����" << endl;
		d = male_queue.get_first();
		cout <<d.name<<"���������ȵõ����"<< endl;
	}
	else if (!female_queue.is_empty()) {
		cout << "����" << female_queue.get_length() << "λŮ�����ڵȴ����" << endl;
		d = female_queue.get_first();
		cout << d.name << "Ůʿ�����ȵõ����" << endl;
	}
	else {
		cout << "û�еȴ�������" << endl;
	}
	cout << endl;

	system("pause");
	return 0;
}