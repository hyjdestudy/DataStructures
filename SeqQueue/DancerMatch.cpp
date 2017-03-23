#include <iostream>
using namespace std;
#include "SeqQueue.h"

//定义队列元素
struct Dancer {
	char name[20];
	char gender;  //性别，'M'表示男，'F'表示女
};

typedef Dancer ElemType;

int main() {
	SeqQueue<ElemType> male_queue(50), female_queue(50);  //建立两个男女队列
	Dancer d;
	cout << "请依次输入舞者的姓名和性别（M/F），以空格分隔，以‘# #’结束：" << endl;
	cin >> d.name >> d.gender;
	while (d.gender != '#') {
		if (d.gender == 'M' || d.gender == 'm') {
			male_queue.append(d);
		}
		else if (d.gender == 'F' || d.gender == 'f') {
			female_queue.append(d);
		}
		else {
			cout << "性别输入错误，请重新输入性别：";
			cin >> d.gender;
			continue;
		}
		cin >> d.name >> d.gender;
	}
	cout << endl;
	cout << "--舞伴配对结果--" << endl;
	while (!male_queue.is_empty() && !female_queue.is_empty()) {
		cout << "男方：";
		d = male_queue.get_first();
		male_queue.remove();
		cout << d.name<<"\t";
		cout << "女方：";
		d = female_queue.get_first();
		female_queue.remove();
		cout << d.name << endl;
	}
	cout << endl;
	if (!male_queue.is_empty()) {
		cout << "还有" << male_queue.get_length() << "位男舞者在等待舞伴" << endl;
		d = male_queue.get_first();
		cout <<d.name<<"先生将最先得到舞伴"<< endl;
	}
	else if (!female_queue.is_empty()) {
		cout << "还有" << female_queue.get_length() << "位女舞者在等待舞伴" << endl;
		d = female_queue.get_first();
		cout << d.name << "女士将最先得到舞伴" << endl;
	}
	else {
		cout << "没有等待的舞者" << endl;
	}
	cout << endl;

	system("pause");
	return 0;
}