//迷宫类
#include <iostream>
#include <iomanip>
using namespace std;
#include "SeqStack.h"
#define MAXSIZE 30  //最大路径长度（最大栈容量）

struct Position {  //迷宫的每个点都用坐标来表示
	int x;
	int y;
};

struct StepRec {  //栈中元素：历史脚步，要记录从哪个点走的，往哪个方向走的
	Position pos;
	int direction;  //0:东  1:南  2:西  3:北  顺时针方向试探
};

class Maze {
private:
	int **maze_m;  //迷宫数组（指向指针的指针：指针maze_m指向一块内存，这块内存里存的是另外一个指针*maze_m）
	int m_row;  //迷宫的行
	int m_col;  //迷宫的列
	Position get_next_pos(Position cur, int dire);  //0.当前在cur处，往dire方向走一步，到达next_pos处
public:
	Maze(int row, int col);  //1.构造空白迷宫
	~Maze();  //2.删除迷宫
	void input();  //3.输入迷宫信息（构造哪里是通路，哪里是死路，并加上一圈围墙）
	bool hasPath(Position start, Position end);  //4.迷宫m中是否存在一条从start到end的通路
	void show_path();  //5.输出迷宫的解

};

//0.当前在cur处，往dire方向走一步，到达新的cur处
Position Maze::get_next_pos(Position cur, int dire) {
	//东南西北，顺时针方向各自步长，{行增量，列增量}
	Position pace[4] = {
		{ 0,1 },
		{ 1,0 },
		{ 0,-1 },
		{ -1,0 }
	};
	cur.x += pace[dire].x;  //根据选择的方向，东西（水平）移动
	cur.y += pace[dire].y;  //根据选择的方向，南北（垂直）移动
	return cur;  //返回新的坐标位置
}

//1.构造函数，迷宫大小为row*col，在外面修一圈围墙，所以数组大小为(row+2)*(col+2)
Maze::Maze(int row, int col) {
	m_row = row + 2;
	m_col = col + 2;
	maze_m = new int *[m_row];
	int i = 0;
	for (i = 0; i < m_row; i++) {
		maze_m[i] = new int[m_col];
	}
}

//2.析构函数
Maze::~Maze() {
	int i = 0;
	for (i = 0; i < m_row; i++) {
		if (maze_m[i] != NULL) {
			delete[] maze_m[i];
		}
	}
	if (maze_m != NULL) {
		delete[] maze_m;
	}
}

//3.输入迷宫
void Maze::input() {
	int i = 0, j = 0;
	cout << "请输入一个" << m_row - 2 << " * " << m_col - 2 << "的迷宫（0代表可通过，1代表不可通过）：" << endl;
	for (i = 1; i <= m_row - 2; i++) {
		for (j = 1; j <= m_col - 2; j++) {
			cin >> maze_m[i][j];
		}
	}
	//设定四周的围墙
	for (i = 0; i < m_row; i++) {
		maze_m[i][0] = 1;
		maze_m[i][m_col - 1] = 1;
	}
	for (j = 0; j < m_col; j++) {
		maze_m[0][j] = 1;
		maze_m[m_row - 1][j] = 1;
	}
}

//4.走迷宫
bool Maze::hasPath(Position start, Position end) {
	SeqStack<StepRec> path(MAXSIZE);  //创建栈，通过记录脚印step来创建一个路径path
	StepRec step_rec;  //存储历史路径
	int cur_step = 1;  //当前足迹，初值为1
	Position cur_pos = start;  //从start处开始走

	do {
		if (maze_m[cur_pos.x][cur_pos.y] == 0) {  //当前位置可以通过，0表示还未走过这个点			
			maze_m[cur_pos.x][cur_pos.y] = cur_step;  //往这个点走，点cur_pos标上“这是第cur_step个脚印”
													  //创建脚步历史记录                                       --------------------一会儿试一下直接赋值step_rec.pos = cur_pos;-------
			step_rec.pos.x = cur_pos.x;
			step_rec.pos.y = cur_pos.y;
			step_rec.direction = 0;  //先让他往东走
			path.push(step_rec);  //把这个脚步记录入栈
			cur_step++;  //下一步的编号

			if (cur_pos.x == end.x && cur_pos.y == end.y) {  //在尝试的过程中，当前位置已到达出口位置，此时path里面就是一条完整路径
				return true;
			}
			//获得下一个要走的位置
			cur_pos = get_next_pos(cur_pos, step_rec.direction);
		}
		else {  //当前位置不能通过
			if (!path.is_empty()) {  //当前位置能退一步
				step_rec = path.get_top();
				path.pop();  //退栈
				cur_step--;  //修改记录的步数

							 //弹出来的记录已经尝试完了所有方向，但是还能接着悔棋，弹到有方向没选或者弹空为止
				while (step_rec.direction == 3 && !path.is_empty()) {
					maze_m[step_rec.pos.x][step_rec.pos.y] = -1;  //已经尝试完该点的所有方向，但是走不通，留下走不通的标记-1
					step_rec = path.get_top();  //再接着悔棋，后退一步
					path.pop();
					cur_step--;  //每退一步，脚步记录减1
				}
				//当前位置还有方向没有尝试
				if (step_rec.direction < 3) {
					step_rec.direction++;  //顺时针方向，尝试下一个方向走走
					path.push(step_rec);  //记录新脚步
					cur_step++;  //每有一个新脚步入栈，脚步编号就要加1
					cur_pos = get_next_pos(step_rec.pos, step_rec.direction);  //到达新位置
				}
			}
		}
	} while (!path.is_empty());  //只要没弹空，一直试，while里面有试成功的时候，直接退出程序

	return false;  //如果从while里正常出来了，说明没有找到能走通的路，则这个迷宫本身就走不出来
}

//5.输出迷宫的解
void Maze::show_path() {
	int i = 0, j = 0;
	for (i = 1; i < m_row - 1; i++) {
		for (j = 1; j < m_col - 1; j++) {
			//if (maze_m[i][j] >= 0 && maze_m[i][j] <= 10) {  //正常输出墙、脚印记录，如果脚印标号是个位数，多输出一个空格
			//	cout << "   " << maze_m[i][j];
			//}
			//else {  //如果是两位数，少输出一个空格
			//	cout << "  " << maze_m[i][j];
			//}
			cout << setw(5) << maze_m[i][j];
		}
		cout << endl;
	}
}
