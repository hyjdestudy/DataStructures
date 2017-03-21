//�Թ���
#include <iostream>
#include <iomanip>
using namespace std;
#include "SeqStack.h"
#define MAXSIZE 30  //���·�����ȣ����ջ������

struct Position {  //�Թ���ÿ���㶼����������ʾ
	int x;
	int y;
};

struct StepRec {  //ջ��Ԫ�أ���ʷ�Ų���Ҫ��¼���ĸ����ߵģ����ĸ������ߵ�
	Position pos;
	int direction;  //0:��  1:��  2:��  3:��  ˳ʱ�뷽����̽
};

class Maze {
private:
	int **maze_m;  //�Թ����飨ָ��ָ���ָ�룺ָ��maze_mָ��һ���ڴ棬����ڴ�����������һ��ָ��*maze_m��
	int m_row;  //�Թ�����
	int m_col;  //�Թ�����
	Position get_next_pos(Position cur, int dire);  //0.��ǰ��cur������dire������һ��������next_pos��
public:
	Maze(int row, int col);  //1.����հ��Թ�
	~Maze();  //2.ɾ���Թ�
	void input();  //3.�����Թ���Ϣ������������ͨ·����������·��������һȦΧǽ��
	bool hasPath(Position start, Position end);  //4.�Թ�m���Ƿ����һ����start��end��ͨ·
	void show_path();  //5.����Թ��Ľ�

};

//0.��ǰ��cur������dire������һ���������µ�cur��
Position Maze::get_next_pos(Position cur, int dire) {
	//����������˳ʱ�뷽����Բ�����{��������������}
	Position pace[4] = {
		{ 0,1 },
		{ 1,0 },
		{ 0,-1 },
		{ -1,0 }
	};
	cur.x += pace[dire].x;  //����ѡ��ķ��򣬶�����ˮƽ���ƶ�
	cur.y += pace[dire].y;  //����ѡ��ķ����ϱ�����ֱ���ƶ�
	return cur;  //�����µ�����λ��
}

//1.���캯�����Թ���СΪrow*col����������һȦΧǽ�����������СΪ(row+2)*(col+2)
Maze::Maze(int row, int col) {
	m_row = row + 2;
	m_col = col + 2;
	maze_m = new int *[m_row];
	int i = 0;
	for (i = 0; i < m_row; i++) {
		maze_m[i] = new int[m_col];
	}
}

//2.��������
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

//3.�����Թ�
void Maze::input() {
	int i = 0, j = 0;
	cout << "������һ��" << m_row - 2 << " * " << m_col - 2 << "���Թ���0�����ͨ����1������ͨ������" << endl;
	for (i = 1; i <= m_row - 2; i++) {
		for (j = 1; j <= m_col - 2; j++) {
			cin >> maze_m[i][j];
		}
	}
	//�趨���ܵ�Χǽ
	for (i = 0; i < m_row; i++) {
		maze_m[i][0] = 1;
		maze_m[i][m_col - 1] = 1;
	}
	for (j = 0; j < m_col; j++) {
		maze_m[0][j] = 1;
		maze_m[m_row - 1][j] = 1;
	}
}

//4.���Թ�
bool Maze::hasPath(Position start, Position end) {
	SeqStack<StepRec> path(MAXSIZE);  //����ջ��ͨ����¼��ӡstep������һ��·��path
	StepRec step_rec;  //�洢��ʷ·��
	int cur_step = 1;  //��ǰ�㼣����ֵΪ1
	Position cur_pos = start;  //��start����ʼ��

	do {
		if (maze_m[cur_pos.x][cur_pos.y] == 0) {  //��ǰλ�ÿ���ͨ����0��ʾ��δ�߹������			
			maze_m[cur_pos.x][cur_pos.y] = cur_step;  //��������ߣ���cur_pos���ϡ����ǵ�cur_step����ӡ��
													  //�����Ų���ʷ��¼                                       --------------------һ�����һ��ֱ�Ӹ�ֵstep_rec.pos = cur_pos;-------
			step_rec.pos.x = cur_pos.x;
			step_rec.pos.y = cur_pos.y;
			step_rec.direction = 0;  //������������
			path.push(step_rec);  //������Ų���¼��ջ
			cur_step++;  //��һ���ı��

			if (cur_pos.x == end.x && cur_pos.y == end.y) {  //�ڳ��ԵĹ����У���ǰλ���ѵ������λ�ã���ʱpath�������һ������·��
				return true;
			}
			//�����һ��Ҫ�ߵ�λ��
			cur_pos = get_next_pos(cur_pos, step_rec.direction);
		}
		else {  //��ǰλ�ò���ͨ��
			if (!path.is_empty()) {  //��ǰλ������һ��
				step_rec = path.get_top();
				path.pop();  //��ջ
				cur_step--;  //�޸ļ�¼�Ĳ���

							 //�������ļ�¼�Ѿ������������з��򣬵��ǻ��ܽ��Ż��壬�����з���ûѡ���ߵ���Ϊֹ
				while (step_rec.direction == 3 && !path.is_empty()) {
					maze_m[step_rec.pos.x][step_rec.pos.y] = -1;  //�Ѿ�������õ�����з��򣬵����߲�ͨ�������߲�ͨ�ı��-1
					step_rec = path.get_top();  //�ٽ��Ż��壬����һ��
					path.pop();
					cur_step--;  //ÿ��һ�����Ų���¼��1
				}
				//��ǰλ�û��з���û�г���
				if (step_rec.direction < 3) {
					step_rec.direction++;  //˳ʱ�뷽�򣬳�����һ����������
					path.push(step_rec);  //��¼�½Ų�
					cur_step++;  //ÿ��һ���½Ų���ջ���Ų���ž�Ҫ��1
					cur_pos = get_next_pos(step_rec.pos, step_rec.direction);  //������λ��
				}
			}
		}
	} while (!path.is_empty());  //ֻҪû���գ�һֱ�ԣ�while�������Գɹ���ʱ��ֱ���˳�����

	return false;  //�����while�����������ˣ�˵��û���ҵ�����ͨ��·��������Թ�������߲�����
}

//5.����Թ��Ľ�
void Maze::show_path() {
	int i = 0, j = 0;
	for (i = 1; i < m_row - 1; i++) {
		for (j = 1; j < m_col - 1; j++) {
			//if (maze_m[i][j] >= 0 && maze_m[i][j] <= 10) {  //�������ǽ����ӡ��¼�������ӡ����Ǹ�λ���������һ���ո�
			//	cout << "   " << maze_m[i][j];
			//}
			//else {  //�������λ���������һ���ո�
			//	cout << "  " << maze_m[i][j];
			//}
			cout << setw(5) << maze_m[i][j];
		}
		cout << endl;
	}
}
