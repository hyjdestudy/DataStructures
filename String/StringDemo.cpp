#include <iostream>
using namespace std;
#include "my_string.h"

int main() {
	char *user_str1 = new char[100];
	char *user_str2 = new char[100];
	MyString str1,str2;
	cout << "�������һ���ַ�����" << endl;
	cin >> user_str1;
	str1.assign_str(user_str1);
	cout << "������ڶ����ַ�����" << endl;
	cin >> user_str2;
	str2.assign_str(user_str2);
	cout << endl;

	cout << "--�ַ�����Ϣ--" << endl;
	cout << "�ַ���1��" << endl;
	str1.show_infor();
	cout << "�ַ���2��" << endl;
	str2.show_infor();
	cout << endl;

	cout << "--�ַ����Ƚϴ�С--" << endl;
	int result=str1.compare(str2);
	char res = '=';
	if (result > 0)
		res = '>';
	else if (result < 0)
		res = '<';
	else {
		res = '=';
	}
	str1.show();
	cout << res;
	str2.show();
	cout << endl;
	cout << endl;

	cout << "--�ַ�������--" << endl;
	cout << "��";
	str2.show();
	cout << "���ӵ�";
	str1.show();
	cout << "����" << endl;
	str1.connect(str2);
	str1.show_infor();
	cout << endl;

	cout << "--����ȡ�Ӵ�--" << endl;
	str1.show();
	cout << endl;
	int start = 0, end = 0;
	cout << "�Ϸ���ֹ�㣺0-" << str1.get_length() - 1 << endl;
	cout << "����������±꣺";
	cin >> start;
	cout << "�������յ��±꣺";
	cin >> end;
	char *sub = new char;
	sub = str1.get_substring(start,end);
	if (sub!=NULL) {
		cout << "��ȡ���Ӵ�Ϊ��" << sub << endl;
	}
	else {
		cout << "��ȡΪ�մ���" << endl;
	}
	cout << endl;

	cout << "--������մ�--" << endl;
	str1.clear();
	str1.show_infor();
	cout << endl;
	system("pause");
	return 0;
}