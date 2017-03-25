#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
#define MAX_LENGTH 100

int simple_match(char *str, char *substr);  //1.简单模式匹配
int * get_next(char *substr);  //2.首先获得next[]数组
int *get_next_val(char *substr);  //2'.改进的获得next[]数组
int kmp(char *str, char *substr, int *next);  //3.采用next[]数组，改进简单模式匹配即可得到kmp算法


int main() {
	char *str=new char[MAX_LENGTH];
	char *substr = new char[MAX_LENGTH];
	int pos = 0;
	cout << "请输入母串（不超过100个字符）：" << endl;
	cin >> str;
	cout << "请输入子串（不超过"<<strlen(str)<<"个字符）：" << endl;
	cin >> substr;
	cout << endl;
	cout << "--采用简单模式匹配--" << endl;
	pos = simple_match(str,substr);
	if (pos >= 0) {
		cout << "子串" << substr << "首次出现于母串" << str << "下标为" << pos << "的位置" << endl;
	}
	else {
		cout << "没有在母串中搜索到子串" << endl;
	}
	cout << endl;

	cout << "--采用KMP模式匹配--" << endl;
	int *next = get_next(substr);
	cout << "子串"<<substr<<"的next数组："<<endl;
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
		cout << "子串" << substr << "首次出现于母串" << str << "下标为" << pos << "的位置" << endl;
	}
	else {
		cout << "没有在母串中搜索到子串" << endl;
	}
	cout << endl;

	cout << "--采用改进next数组的KMP模式匹配--" << endl;
	int *nextval = get_next_val(substr);
	cout << "子串" << substr << "的next数组：" << endl;
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
		cout << "子串" << substr << "首次出现于母串" << str << "下标为" << pos << "的位置" << endl;
	}
	else {
		cout << "没有在母串中搜索到子串" << endl;
	}
	cout << endl;
	system("pause");
	return 0;
}

//1.简单模式匹配
int simple_match(char *str, char *substr) {
	int i = 0, j = 0, next_i = i + 1;  //i用于遍历母串，j用于遍历子串，next_i用于回到本趟开始时i的下一个位置
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

//2.获取next[]数组
int * get_next(char *substr) {
	int t_len = strlen(substr);  //获得模式串substr的长度
	int *next=new int[t_len];  //根据substr的长度做next数组
	int i = 0;
	/*
	用i去遍历substr，表示第i个位置发生冲突，需要对应一个next[i]去解决
	*/
	int j = -1;
	/*
	j记录最长前缀串的后一个位置，看看下一个位置能不能直接并到前缀串里，
	j==-1表示substr的首位都冲突了，
	*/
	next[0] = -1;
	/*（这是一个特殊情况）
	0处发生冲突，则一开始就没匹配上，需要母串右移一位放弃这个和模式首位冲突的位置，
	同时模式substr串也右移一位，从0开始重新匹配
	*/
	
	while (i < t_len) {  //由substr[i]求substr[i+1]
		if (j==-1 || substr[i]==substr[j]) {
			/*
			j==-1表示上次匹配和substr的首位都冲突了，那就跳过母串的i位，第i+1位和模式串头（j=0）开始
			substr[i]==substr[j]，冲突位和前缀串的下一位j一样，则next[i+1]=next[i]+1，即next[i]=j
			（next[i+1]=next[i]+1的情况）
			*/
			i++;  //i指示要求当前冲突位的next[i]，i只会往后走或者不走
			j++;  
			/*
			如果刚才找到的最长前缀的后一位恰好和当前冲突位一样，就是说还能构成前缀，
			就让j再往后走一个，指向新最长前缀的后一个位置，即从next[i]求出了next[i+1]=next[i]+1
			*/
			next[i] = j;
		}
		else {
			j = next[j];  //如果最长前缀后一位和当前冲突位不一样，那就用解决冲突位为j的方法next[j]去解决
		}
	}
	return next;
}

//2'.改进的获得next[]数组
int *get_next_val(char *substr) {
	/*
	针对母串：aaaaabaaaaaaab和子串：aaaaaab的情况
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
			j = nextval[j];  //如果最长前缀后一位和当前冲突位不一样，那就用解决冲突位为j的方法next[j]去解决
		}
	}
	return nextval;
}

//3.KMP算法
int kmp(char *str, char *substr, int *next) {
	int i = 0, j = 0;
	while (i < strlen(str) && j < strlen(substr)) {
		if (str[i] == substr[j]) {  //匹配上了			
			i++;
			j++;
		}
		else {
			j = next[j];  //j处发生冲突，用next[j]去解决
			if (j == -1) {
				/*
				j==-1说明子串第一个个字母也不能和母串里当前i指向的字符匹配，
				则需要跳过这个i，重新从substr[0]开始比
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

