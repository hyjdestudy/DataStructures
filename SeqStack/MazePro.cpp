//ʹ��˳��ջʵ�����Թ�
#include <iostream>
using namespace std;
#include "MazeFun.h"

int main() {
	int m = 0, n = 0;  //�Թ���СΪm*n
	Position start, end;  //�Թ��������յ�
	do {
		cout << "�������Թ���������";
		cin >> m;
		cout << "�������Թ���������";
		cin >> n;
	} while (m<=0 || n<=0);
	Maze my_maze(m,n);  //��ʼ���Թ�
	my_maze.input();
	cout << "��������Թ�Ϊ��" << endl;
	my_maze.show_path();
	cout << endl;

	cout << "��ָ���Թ�����ڣ��к� �кţ���";
	cin >> start.x >> start.y;
	cout << "��ָ���Թ��ĳ��ڣ��к� �кţ���";
	cin >> end.x >> end.y;
	cout << endl;

	if (my_maze.hasPath(start,end)) {
		cout << "��ǰ�Թ�������ͨ��·�����£�" << endl;
		my_maze.show_path();
	}
	else {
		cout << "��ǰ�Թ�������ͨ��" << endl;
	}
	cout << endl;
	system("pause");
	return 0;
}