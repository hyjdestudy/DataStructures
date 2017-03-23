/*
一列火车有n个车厢，这n个车厢是无序的，现经过一个火车站，要把车厢排好序
输入轨：乱序火车开进来
输出轨：有序火车开出去
缓冲轨：用于重排车厢的轨道
注意：不是所有的车厢都能排好序，这个和可用的缓冲轨数量有关

分析：
缓冲轨里存的是暂时有序的车厢，车厢之间可能不连续，但编号都是从小到大，如：1,2,4；3,6,9等
所以每个缓冲轨的最后一节车厢一定是当前缓冲轨里最大号的车厢
要把当前输入轨的队头车厢放到一个合适的缓冲轨里，要保证这个队头车厢号比要放入的缓冲轨最末一节车厢号大
可能有多条缓冲轨满足这个条件，所以要挑一个最优的缓冲轨，即这个缓冲轨队尾的车厢编号是最大的
之后把输入轨队头的车厢移入这个最优的缓冲轨队尾
如果不存在合适的缓冲轨，那就要选一个空的缓冲轨，把输入轨队头的车厢移入这个空缓冲轨中
如果没有空缓冲轨可用，那就说明这列火车的车厢不能重排
*/
#include <iostream>
using namespace std;
#include "SeqQueue.h"

//火车站
class TrackStation {
private:
	int track_num;  //缓冲轨条数
	SeqQueue<int> *tracks;  //存放多条缓冲轨
	bool put_in(int carriage);  //把车厢carriage移动到缓冲轨上
	bool put_out(int carri);  //把车厢carri从缓冲轨移动到输出轨上
public:
	TrackStation(int track_n);  //1.构造函数
	~TrackStation();  //2.析构函数
	bool realign(int *carriages, int n);  //3.重排车厢
};


//1.用参数初始化表对数据成员进行初始化
TrackStation::TrackStation(int track_n) :track_num(track_n) {
	tracks = new SeqQueue<int> [track_num];  //建立一个有track_num条缓冲轨的数组，数组的每个元素都是一个缓冲轨
}

//2.销毁火车站
TrackStation::~TrackStation() {
	delete[] tracks;
}

//3.把车厢carriage移入一个最优的缓冲轨
bool TrackStation::put_in(int carriage) {
	int best_track = -1;  //最优缓冲轨的编号
	int best_carri = -1;  //最优车厢位，是最优缓冲轨的最后一节车厢编号
	int last_carri = -1;  //缓冲轨最后一节车厢的编号
	int i = 0;
	for (i = 0; i < track_num; i++) {  //寻找最优缓冲轨
		if (!tracks[i].is_empty()) {  //先查已经有车厢的缓冲轨
			last_carri = tracks[i].get_last();  //查当前缓冲轨的最后一节车厢号
			if (carriage>last_carri && last_carri > best_carri) {  //当前车厢可以放入该缓冲轨，且该缓冲轨比上次找到的还优
				best_track = i;  //把当前缓冲轨置为最优缓冲轨
				best_carri = last_carri;  //修改当前最优车厢位
			}
		}
	}  //寻找最优缓冲轨结束

	if (best_track == -1) {  //有车厢的缓冲轨都不合适，找空缓冲轨
		for (i = 0; i < track_num; i++) {
			if (tracks[i].is_empty()) {  //找到一条空缓冲轨
				best_track = i;  //把该空缓冲轨置为最优缓冲轨
				break;
			}
		}
	}

	if (best_track == -1) {  //没有找到合适的缓冲轨，无论是有车厢的还是空的
		return false;  //这个车厢没地儿放，不能进行车厢重排
	}

	tracks[best_track].append(carriage);  //把车厢放到最优缓冲轨上
	cout << carriage << "号车厢进入" << best_track << "号缓冲轨" << endl;
	return true;
}

//4.把某个车厢从缓冲轨移动到输出轨上（车厢只有在缓冲轨队头时，才能直接出站）
bool TrackStation::put_out(int carriage) {
	int i = 0;
	for (i = 0; i < track_num; i++) {  //遍历缓冲轨，找车厢carriage
		if (!tracks[i].is_empty()) {
			int first_carriage = tracks[i].get_first();  //获得当前缓冲轨的第一节车厢
			if (first_carriage == carriage) {  //找到了要出去的车厢
				first_carriage = tracks[i].get_first();
				tracks[i].remove();
				cout <<first_carriage<< "号车厢从"<<i<< "号缓冲轨出站" << endl;
				return true;
			}
		}
	}
	return false;
}

//5.利用缓冲轨重排n个车厢
bool TrackStation::realign(int *carriages, int n) {
	int now_out = 1;  //now_out表示现在该num_out号车厢正确出站了，如：现在该1号了，该2号了，，，该num_out号了，，，
	int i = 0;
	/*
	i用于遍历输入轨上的乱序车厢。
	num_out号要想出站，必须先进入缓冲轨并占据队头位置才能出。
	但是num_out号车厢可能排在输入轨靠后的位置，num_out号要想进缓冲轨，必须让排在它前面的那几个车厢先进入缓冲轨。
	所以每次要让num_out号出站时，只要他不是马上出来，就说明输入轨里有人再他前面挡着。
	用i去遍历输入轨，让这些挡着的一一进入缓冲轨，进几节说不定就能让num_out号进入缓冲轨，然后正确出站，
	一旦有没成功进入缓冲轨的，就说明num_out只能被挡在后面进不了缓冲轨，
	也就是说没法正确调整出轨顺序，火车车厢无法正确排序。
	而还有一种错误就是，用户输入序列时中间少输入了几节车厢号，导致这个序列本来就不连续，
	则i在自增遍历时，可能会自增到超过n，此时直接返回false即可，表示不能正确排序
	*/	
	while (now_out <= n) {
		if (put_out(now_out)) {  //第now_out节车厢成功出站
			now_out++;
			continue;
		}
		if (!put_in(carriages[i]) || i >= n)  //编号为i的车厢没法进入缓冲轨  或者 用户输入的序列本身有误
			return false;
		i++;
	}
	return true;
}

int main() {
	int num_of_tracks=0;
	cout << "请输入缓冲轨的数目：";
	do {
		cin >> num_of_tracks;
	} while (num_of_tracks<0);

	//建立火车站
	TrackStation station(num_of_tracks);
	int carri,carris[100];
	int i = 0;
	cout << "--输入入轨的车厢次序，以0结束--" << endl;
	do {
		cout << "请输入第" << i + 1 << "节车厢的编号：";
		cin >> carri;
		if (carri > 0) {
			carris[i] = carri;
			i++;
		}
	} while (carri>0);
	cout << endl;
	cout << "--车厢入轨与出轨情况--" << endl;
	if (!station.realign(carris, i)) {
		cout << "车厢无法重排！" << endl;
	}
	cout << endl;
	system("pause");
	return 0;
}