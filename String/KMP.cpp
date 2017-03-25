#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
#define MAX_LENGTH 100

int simple_match(char *str, char *substr);  //1.��ģʽƥ��
int * get_next(char *substr);  //2.���Ȼ��next[]����
int *get_next_val(char *substr);  //2'.�Ľ��Ļ��next[]����
int kmp(char *str, char *substr, int *next);  //3.����next[]���飬�Ľ���ģʽƥ�伴�ɵõ�kmp�㷨


int main() {
	char *str=new char[MAX_LENGTH];
	char *substr = new char[MAX_LENGTH];
	int pos = 0;
	cout << "������ĸ����������100���ַ�����" << endl;
	cin >> str;
	cout << "�������Ӵ���������"<<strlen(str)<<"���ַ�����" << endl;
	cin >> substr;
	cout << endl;
	cout << "--���ü�ģʽƥ��--" << endl;
	pos = simple_match(str,substr);
	if (pos >= 0) {
		cout << "�Ӵ�" << substr << "�״γ�����ĸ��" << str << "�±�Ϊ" << pos << "��λ��" << endl;
	}
	else {
		cout << "û����ĸ�����������Ӵ�" << endl;
	}
	cout << endl;

	cout << "--����KMPģʽƥ��--" << endl;
	int *next = get_next(substr);
	cout << "�Ӵ�"<<substr<<"��next���飺"<<endl;
	int i = 0;
	for (i = 0; i < strlen(substr); i++) {
		cout << setw(4)<< substr[i];
	}
	cout << endl;
	for (i = 0; i < strlen(substr); i++) {
		cout << setw(4) << next[i];
	}
	cout << endl;
	pos = kmp(str,substr,next);
	if (pos >= 0) {
		cout << "�Ӵ�" << substr << "�״γ�����ĸ��" << str << "�±�Ϊ" << pos << "��λ��" << endl;
	}
	else {
		cout << "û����ĸ�����������Ӵ�" << endl;
	}
	cout << endl;

	cout << "--���øĽ�next�����KMPģʽƥ��--" << endl;
	int *nextval = get_next_val(substr);
	cout << "�Ӵ�" << substr << "��next���飺" << endl;
	i = 0;
	for (i = 0; i < strlen(substr); i++) {
		cout << setw(4) << substr[i];
	}
	cout << endl;
	for (i = 0; i < strlen(substr); i++) {
		cout << setw(4) << nextval[i];
	}
	cout << endl;
	pos = kmp(str, substr, nextval);
	if (pos >= 0) {
		cout << "�Ӵ�" << substr << "�״γ�����ĸ��" << str << "�±�Ϊ" << pos << "��λ��" << endl;
	}
	else {
		cout << "û����ĸ�����������Ӵ�" << endl;
	}
	cout << endl;
	system("pause");
	return 0;
}

//1.��ģʽƥ��
int simple_match(char *str, char *substr) {
	int i = 0, j = 0, next_i = i + 1;  //i���ڱ���ĸ����j���ڱ����Ӵ���next_i���ڻص����˿�ʼʱi����һ��λ��
	while (i < strlen(str) && j < strlen(substr)) {
		if (str[i] == substr[j]) {
			i++;
			j++;
		}
		else {
			i = next_i;
			next_i ++;
			j = 0;
		}
	}
	if (j >= strlen(substr)) {
		return next_i-1;
	}
	return -1;
}

//2.��ȡnext[]����
int * get_next(char *substr) {
	int t_len = strlen(substr);  //���ģʽ��substr�ĳ���
	int *next=new int[t_len];  //����substr�ĳ�����next����
	int i = 0;
	/*
	��iȥ����substr����ʾ��i��λ�÷�����ͻ����Ҫ��Ӧһ��next[i]ȥ���
	*/
	int j = -1;
	/*
	j��¼�ǰ׺���ĺ�һ��λ�ã�������һ��λ���ܲ���ֱ�Ӳ���ǰ׺���
	j==-1��ʾsubstr����λ����ͻ�ˣ�
	*/
	next[0] = -1;
	/*������һ�����������
	0��������ͻ����һ��ʼ��ûƥ���ϣ���Ҫĸ������һλ���������ģʽ��λ��ͻ��λ�ã�
	ͬʱģʽsubstr��Ҳ����һλ����0��ʼ����ƥ��
	*/
	
	while (i < t_len) {  //��substr[i]��substr[i+1]
		if (j==-1 || substr[i]==substr[j]) {
			/*
			j==-1��ʾ�ϴ�ƥ���substr����λ����ͻ�ˣ��Ǿ�����ĸ����iλ����i+1λ��ģʽ��ͷ��j=0����ʼ
			substr[i]==substr[j]����ͻλ��ǰ׺������һλjһ������next[i+1]=next[i]+1����next[i]=j
			��next[i+1]=next[i]+1�������
			*/
			i++;  //iָʾҪ��ǰ��ͻλ��next[i]��iֻ�������߻��߲���
			j++;  
			/*
			����ղ��ҵ����ǰ׺�ĺ�һλǡ�ú͵�ǰ��ͻλһ��������˵���ܹ���ǰ׺��
			����j��������һ����ָ�����ǰ׺�ĺ�һ��λ�ã�����next[i]�����next[i+1]=next[i]+1
			*/
			next[i] = j;
		}
		else {
			j = next[j];  //����ǰ׺��һλ�͵�ǰ��ͻλ��һ�����Ǿ��ý����ͻλΪj�ķ���next[j]ȥ���
		}
	}
	return next;
}

//2'.�Ľ��Ļ��next[]����
int *get_next_val(char *substr) {
	/*
	���ĸ����aaaaabaaaaaaab���Ӵ���aaaaaab�����
	*/
	int t_len = strlen(substr);
	int *nextval = new int[t_len]; 
	int i = 0;
	int j = -1;
	nextval[0] = -1;

	while (i < t_len) { 
		if (j == -1 || substr[i] == substr[j]) {
			i++;  
			j++;
			if (substr[i] != substr[j])
				nextval[i] = j;
			else
				nextval[i] = nextval[j];
		}
		else {
			j = nextval[j];  //����ǰ׺��һλ�͵�ǰ��ͻλ��һ�����Ǿ��ý����ͻλΪj�ķ���next[j]ȥ���
		}
	}
	return nextval;
}

//3.KMP�㷨
int kmp(char *str, char *substr, int *next) {
	int i = 0, j = 0;
	while (i < strlen(str) && j < strlen(substr)) {
		if (str[i] == substr[j]) {  //ƥ������			
			i++;
			j++;
		}
		else {
			j = next[j];  //j��������ͻ����next[j]ȥ���
			if (j == -1) {
				/*
				j==-1˵���Ӵ���һ������ĸҲ���ܺ�ĸ���ﵱǰiָ����ַ�ƥ�䣬
				����Ҫ�������i�����´�substr[0]��ʼ��
				*/
				i++;
				j = 0;
			}
		}
	}
	if (j >= strlen(substr)) {
		return i - strlen(substr);
	}
	return -1;
}

