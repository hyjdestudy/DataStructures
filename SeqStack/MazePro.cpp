//使用顺序栈实现走迷宫
#include <iostream>
using namespace std;
#include "MazeFun.h"

int main() {
	int m = 0, n = 0;  //迷宫大小为m*n
	Position start, end;  //迷宫的起点和终点
	do {
		cout << "请输入迷宫的行数：";
		cin >> m;
		cout << "请输入迷宫的列数：";
		cin >> n;
	} while (m<=0 || n<=0);
	Maze my_maze(m,n);  //初始化迷宫
	my_maze.input();
	cout << "您构造的迷宫为：" << endl;
	my_maze.show_path();
	cout << endl;

	cout << "请指定迷宫的入口（行号 列号）：";
	cin >> start.x >> start.y;
	cout << "请指定迷宫的出口（行号 列号）：";
	cin >> end.x >> end.y;
	cout << endl;

	if (my_maze.hasPath(start,end)) {
		cout << "当前迷宫可以走通，路径如下：" << endl;
		my_maze.show_path();
	}
	else {
		cout << "当前迷宫不能走通！" << endl;
	}
	cout << endl;
	system("pause");
	return 0;
}