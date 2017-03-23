/*
һ�л���n�����ᣬ��n������������ģ��־���һ����վ��Ҫ�ѳ����ź���
����죺����𳵿�����
����죺����𳵿���ȥ
����죺�������ų���Ĺ��
ע�⣺�������еĳ��ᶼ���ź�������Ϳ��õĻ���������й�

������
�������������ʱ����ĳ��ᣬ����֮����ܲ�����������Ŷ��Ǵ�С�����磺1,2,4��3,6,9��
����ÿ�����������һ�ڳ���һ���ǵ�ǰ����������ŵĳ���
Ҫ�ѵ�ǰ�����Ķ�ͷ����ŵ�һ�����ʵĻ�����Ҫ��֤�����ͷ����ű�Ҫ����Ļ������ĩһ�ڳ���Ŵ�
�����ж�������������������������Ҫ��һ�����ŵĻ���죬�����������β�ĳ�����������
֮���������ͷ�ĳ�������������ŵĻ�����β
��������ں��ʵĻ���죬�Ǿ�Ҫѡһ���յĻ���죬��������ͷ�ĳ�����������ջ������
���û�пջ������ã��Ǿ�˵�����л𳵵ĳ��᲻������
*/
#include <iostream>
using namespace std;
#include "SeqQueue.h"

//��վ
class TrackStation {
private:
	int track_num;  //���������
	SeqQueue<int> *tracks;  //��Ŷ��������
	bool put_in(int carriage);  //�ѳ���carriage�ƶ����������
	bool put_out(int carri);  //�ѳ���carri�ӻ�����ƶ����������
public:
	TrackStation(int track_n);  //1.���캯��
	~TrackStation();  //2.��������
	bool realign(int *carriages, int n);  //3.���ų���
};


//1.�ò�����ʼ��������ݳ�Ա���г�ʼ��
TrackStation::TrackStation(int track_n) :track_num(track_n) {
	tracks = new SeqQueue<int> [track_num];  //����һ����track_num�����������飬�����ÿ��Ԫ�ض���һ�������
}

//2.���ٻ�վ
TrackStation::~TrackStation() {
	delete[] tracks;
}

//3.�ѳ���carriage����һ�����ŵĻ����
bool TrackStation::put_in(int carriage) {
	int best_track = -1;  //���Ż����ı��
	int best_carri = -1;  //���ų���λ�������Ż��������һ�ڳ�����
	int last_carri = -1;  //��������һ�ڳ���ı��
	int i = 0;
	for (i = 0; i < track_num; i++) {  //Ѱ�����Ż����
		if (!tracks[i].is_empty()) {  //�Ȳ��Ѿ��г���Ļ����
			last_carri = tracks[i].get_last();  //�鵱ǰ���������һ�ڳ����
			if (carriage>last_carri && last_carri > best_carri) {  //��ǰ������Է���û���죬�Ҹû������ϴ��ҵ��Ļ���
				best_track = i;  //�ѵ�ǰ�������Ϊ���Ż����
				best_carri = last_carri;  //�޸ĵ�ǰ���ų���λ
			}
		}
	}  //Ѱ�����Ż�������

	if (best_track == -1) {  //�г���Ļ���춼�����ʣ��ҿջ����
		for (i = 0; i < track_num; i++) {
			if (tracks[i].is_empty()) {  //�ҵ�һ���ջ����
				best_track = i;  //�Ѹÿջ������Ϊ���Ż����
				break;
			}
		}
	}

	if (best_track == -1) {  //û���ҵ����ʵĻ���죬�������г���Ļ��ǿյ�
		return false;  //�������û�ض��ţ����ܽ��г�������
	}

	tracks[best_track].append(carriage);  //�ѳ���ŵ����Ż������
	cout << carriage << "�ų������" << best_track << "�Ż����" << endl;
	return true;
}

//4.��ĳ������ӻ�����ƶ���������ϣ�����ֻ���ڻ�����ͷʱ������ֱ�ӳ�վ��
bool TrackStation::put_out(int carriage) {
	int i = 0;
	for (i = 0; i < track_num; i++) {  //��������죬�ҳ���carriage
		if (!tracks[i].is_empty()) {
			int first_carriage = tracks[i].get_first();  //��õ�ǰ�����ĵ�һ�ڳ���
			if (first_carriage == carriage) {  //�ҵ���Ҫ��ȥ�ĳ���
				first_carriage = tracks[i].get_first();
				tracks[i].remove();
				cout <<first_carriage<< "�ų����"<<i<< "�Ż�����վ" << endl;
				return true;
			}
		}
	}
	return false;
}

//5.���û��������n������
bool TrackStation::realign(int *carriages, int n) {
	int now_out = 1;  //now_out��ʾ���ڸ�num_out�ų�����ȷ��վ�ˣ��磺���ڸ�1���ˣ���2���ˣ�������num_out���ˣ�����
	int i = 0;
	/*
	i���ڱ���������ϵ������ᡣ
	num_out��Ҫ���վ�������Ƚ��뻺��첢ռ�ݶ�ͷλ�ò��ܳ���
	����num_out�ų��������������쿿���λ�ã�num_out��Ҫ�������죬������������ǰ����Ǽ��������Ƚ��뻺��졣
	����ÿ��Ҫ��num_out�ų�վʱ��ֻҪ���������ϳ�������˵�����������������ǰ�浲�š�
	��iȥ��������죬����Щ���ŵ�һһ���뻺��죬������˵����������num_out�Ž��뻺��죬Ȼ����ȷ��վ��
	һ����û�ɹ����뻺���ģ���˵��num_outֻ�ܱ����ں�������˻���죬
	Ҳ����˵û����ȷ��������˳�򣬻𳵳����޷���ȷ����
	������һ�ִ�����ǣ��û���������ʱ�м��������˼��ڳ���ţ�����������б����Ͳ�������
	��i����������ʱ�����ܻ�����������n����ʱֱ�ӷ���false���ɣ���ʾ������ȷ����
	*/	
	while (now_out <= n) {
		if (put_out(now_out)) {  //��now_out�ڳ���ɹ���վ
			now_out++;
			continue;
		}
		if (!put_in(carriages[i]) || i >= n)  //���Ϊi�ĳ���û�����뻺���  ���� �û���������б�������
			return false;
		i++;
	}
	return true;
}

int main() {
	int num_of_tracks=0;
	cout << "�����뻺������Ŀ��";
	do {
		cin >> num_of_tracks;
	} while (num_of_tracks<0);

	//������վ
	TrackStation station(num_of_tracks);
	int carri,carris[100];
	int i = 0;
	cout << "--�������ĳ��������0����--" << endl;
	do {
		cout << "�������" << i + 1 << "�ڳ���ı�ţ�";
		cin >> carri;
		if (carri > 0) {
			carris[i] = carri;
			i++;
		}
	} while (carri>0);
	cout << endl;
	cout << "--���������������--" << endl;
	if (!station.realign(carris, i)) {
		cout << "�����޷����ţ�" << endl;
	}
	cout << endl;
	system("pause");
	return 0;
}