#include <iostream>
using namespace std;
#include "my_string.h"

int main() {
	char *user_str1 = new char[100];
	char *user_str2 = new char[100];
	MyString str1,str2;
	cout << "请输入第一个字符串：" << endl;
	cin >> user_str1;
	str1.assign_str(user_str1);
	cout << "请输入第二个字符串：" << endl;
	cin >> user_str2;
	str2.assign_str(user_str2);
	cout << endl;

	cout << "--字符串信息--" << endl;
	cout << "字符串1：" << endl;
	str1.show_infor();
	cout << "字符串2：" << endl;
	str2.show_infor();
	cout << endl;

	cout << "--字符串比较大小--" << endl;
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

	cout << "--字符串连接--" << endl;
	cout << "把";
	str2.show();
	cout << "连接到";
	str1.show();
	cout << "后面" << endl;
	str1.connect(str2);
	str1.show_infor();
	cout << endl;

	cout << "--测试取子串--" << endl;
	str1.show();
	cout << endl;
	int start = 0, end = 0;
	cout << "合法起止点：0-" << str1.get_length() - 1 << endl;
	cout << "请输入起点下标：";
	cin >> start;
	cout << "请输入终点下标：";
	cin >> end;
	char *sub = new char;
	sub = str1.get_substring(start,end);
	if (sub!=NULL) {
		cout << "截取的子串为：" << sub << endl;
	}
	else {
		cout << "截取为空串！" << endl;
	}
	cout << endl;

	cout << "--测试清空串--" << endl;
	str1.clear();
	str1.show_infor();
	cout << endl;
	system("pause");
	return 0;
}