#include <iostream>
#include "SeqStack.h"  //ʹ��˳��ջ����������ջ��������ջ
#include "exp_evaluation_fun.h"  //���ܺ���ͷ�ļ�
using namespace std;

#define MAX_EXPLENGTH 100  //������ʽ�Ϊ100���ַ�

int main() {
	char *exp;  //�洢�û�����ı��ʽ
	exp = new char[MAX_EXPLENGTH];
	double result = 0;  //�洢������
	int i = 0;  //����ַ������û�������
	cout << "������һ����ȷ������������ʽ��������Ϊ���������ԵȺŽ�β����" << endl;	
	cin >> exp[i];
	while (exp[i] != '=') {
		cin >> exp[++i];
	}
	if (compute_exp(exp, result)) {
		cout << "������Ϊ��" << result << endl;
	}
	else {
		cout << "�������" << endl;
	}
	system("pause");
	return 0;
}

