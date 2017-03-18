/*
description:��ѭ������ʵ��Լɪ������
author:�����
date:2017-03-17
*/

#include <stdio.h>
#include <stdlib.h>

#define ERR_INVALIDPARAM -1  //�Ƿ�����
#define ERR_MEMORY  -2//�ڴ����

typedef struct Pirate {
	int id;  //�����ı��
	struct Pirate *next;
}Pirate,Group;  //�����Pirate��ѭ��������Group

/*��������*/
int init_group(Group *G,int n);  //1.��������n��Ԫ�ص�Լɪ�򻷣���ͷ��㣩
void josephus_op(Group *G,int n);  //2.Լɪ���㷨����ͷ��㣩
Group* init_group_without_head(Group *G, int n);  //3.����n��Ԫ�ص�Լɪ�򻷣�����ͷ��㣩
void josephus_op_without_head(Group *G, int num);  //4.Լɪ���㷨������ͷ��㣩
void show_tail();  //5.��ʾ���

int main() {
	int choice = 1;  //�����û�ѡ��Ĳ˵�
	char ch = ' ';  //���ջس���
	int pirates=0;  //ָ���ж��ٺ���
	int number = 0;  //ָ����������
	Group *G = NULL;  //����Ⱥ
	Group *New_G = NULL;
	int status = 0;  //���ղ�����ִ��״̬
	bool is_active = true;  //��Ϸ�Ƿ����ڽ���

	printf("\t\t\t\t\t----Լɪ�򻷺���������Ϸ----\n\n");
	printf("����������\n");
	printf("n�������ڻĵ��ϣ�ֻ��1��ˮ�����Ǿ���վ��һȦ��1��ʼ������˭������������num����ɱ,"
		"֮����һλ���´�1��ʼ����ֱ��ֻʣ�����һ���ˣ��Ɑˮ������\n");	
	printf("\n");

	while (is_active) {
		//����Լɪ��
		G = (Group*)malloc(sizeof(Pirate));
		if (!G) {
			printf("�ڴ�����쳣���������г���\n");
			system("pause");
			return 0;
		}
		printf("\t\t\t\t\t\t--��Ϸ�˵�--\n");
		printf("\n1.ʹ�ú�ͷ���ĵ�ѭ������\t\t2.ʹ����ͷ���ĵ�ѭ������\t\t3.�˳���Ϸ\n");
		printf("��ѡ��");
		scanf_s("%d", &choice);
		ch = getchar();

		if (choice == 1 || choice == 2) {
			do {
				printf("�����뺣������");
				scanf_s("%d", &pirates);
				ch = getchar();  //���ջس���
				printf("��ָ���������֣�");
				scanf_s("%d", &number);
				ch = getchar();
			} while (pirates<0 || number<0);
		}				
		
		switch (choice)
		{
		case 1:
			printf("\t\t\t\t\t--ʹ�ú�ͷ���ĵ�ѭ������--\n");
			//��������Ⱥ
			status = init_group(G, pirates);
			if (status < 0) {
				printf("��������Ⱥʧ�ܣ��������г���\n");
				system("pause");
				return 0;
			}
			//��������
			josephus_op(G, number);
			show_tail();
			break;
		case 2:
			printf("\t\t\t\t\t--ʹ����ͷ���ĵ�ѭ������--\n");
			//��������Ⱥ
			New_G = init_group_without_head(G, pirates);
			if (!New_G) {
				printf("��������Ⱥʧ�ܣ��������г���\n");
				system("pause");
				return 0;
			}
			//��������
			josephus_op_without_head(New_G, number);
			show_tail();
			break;
		case 3:
			printf("\t\t\t\t\t\t--�˳���Ϸ--\n");
			is_active = false;
			printf("���ѳɹ��˳���Ϸ��\n");
			show_tail();
			break;
		default:
			printf("\t\t\t\t\t\t--ѡ�����--\n");
			printf("�˵��������������ѡ��\n");
			show_tail();
		}
	}

	system("pause");
	return 0;
}

/*����ʵ��*/
//1.����n��Ԫ�ص�Լɪ�򻷣���ͷ��㣩
int init_group(Group *G,int n) {
	if (!G) {
		printf("��Ч��ַ�����ܽ���Լɪ�򻷣�\n");
		return ERR_INVALIDPARAM;
	}
	G->next = G;  //��ʼ��ͷ��㣬��ʱ��ʾ��ѭ������Ϊ��
	Pirate *r = G;  //rָ��ʱ��ָ��ѭ����������һ��λ��
	Pirate *p;  //�������½��
	if (n < 0) {
		printf("���������������0��\n");
		return ERR_INVALIDPARAM;
	}
	int i = 0;
	for (i = 1; i <= n; i++) {
		p = (Pirate*)malloc(sizeof(Pirate));
		if (!p) {
			printf("�����½���쳣��\n");
			return ERR_MEMORY;
		}
		p->id = i;
		//���½��p�ҵ��������һ��λ��
		p->next = r->next;
		r->next = p;
		//rָ�����һ�����
		r = r->next;
	}
	return 1;
}

//2.Լɪ���㷨����ͷ��㣩
void josephus_op(Group *G, int num) {
	if (!G) {
		printf("��Ч��ַ������ִ��Լɪ���㷨��\n");
		system("pause");
		return;
	}
	int count = 1;  //������ӵ�˳��
	int i = 1;  //������
	Pirate *pre = G;  //ָ��ǰ���p��ǰ��
	Pirate *p = G->next;
	Pirate *q;  //�����ͷ��ڴ�

	while (p->next != pre) {  //��ֻʣ��һ���˵�ʱ��ֹͣ��ע�⣺p������ָ��ͷ��㣬Ҳ����ָ�����һ�����ŵĺ�����
		if (p != G) {  //����ͷ���Ͷ��ñ���
			printf("%d�ź���������%d\n", p->id, i);
			if (i == num) {  //����˱�������num��Ҫ��ɱ
				printf("��%d����ɱ�ĺ�����%d�ţ�\n", count++, p->id);
				q = p;  //�ݴ�Ҫɾ���Ľ��
				pre->next = p->next;  
				p = p->next;  //��Ϊɱ��һ��������ǰ�����䣬ֻ��p����Ųһ��
				free(q);
				i = 1;  //���±���
			}
			else {  //û�б����������֣���������
				i++;
				pre = p;
				p = p->next;
			}			
		}
		else {  //ͷ��㲻�ñ���
			pre = p;
			p = p->next;
		}
	}
	printf("\n");
	if (p == G) {  //���p���ָ�����ͷ���G�������Ǻ���
		p = p->next;  
	}
	printf("���������ĺ�����%d��\n",p->id);
}

//3.����n��Ԫ�ص�Լɪ�򻷣�����ͷ��㣩
Pirate* init_group_without_head(Group *G, int n) {
	//���ô�ͷ���ĳ�ʼ������
	int status=init_group(G,n);
	if (status < 0) {
		printf("��ʼ��������ʧ�ܣ����ܽ���Լɪ�򻷣�\n");
		return NULL;
	}
	Pirate *r = G->next;  //��rȥ�����һ�����
	while (r->next != G) {
		r = r->next;
	}
	
	//ȥ��ͷ���
	r->next = G->next;  //�����һ������nextָ��ָ���һ�����
	Pirate *New_G = G->next;
	free(G);
	return New_G;
}

//4.Լɪ���㷨������ͷ��㣩
void josephus_op_without_head(Group *G, int num) {
	if (!G) {
		printf("��Ч��ַ������ִ��Լɪ���㷨��\n");
		system("pause");
		return;
	}
	int count = 1;  //������ӵ�˳��
	int i = 1;  //������
	Pirate *pre = G;  //��preȥ�����һ����㣬����һ������ǰ��
	while (pre->next != G) {
		pre = pre->next;
	}
	Pirate *p = G;  //p����ָ��ǰ���
	Pirate *q;  //�����ͷ��ڴ�

	while (p->next != p) {  //��ֻʣ��һ���˵�ʱ��ֹͣ
		printf("%d�ź���������%d\n", p->id, i);
		if (i == num) {  //����˱�������num��Ҫ��ɱ
			printf("��%d����ɱ�ĺ�����%d�ţ�\n", count++, p->id);
			q = p;  //�ݴ�Ҫɾ���Ľ��
			pre->next = p->next;
			p = p->next;  //��Ϊɱ��һ��������ǰ�����䣬ֻ��p����Ųһ��
			free(q);
			i = 1;  //���±���
		}
		else {  //û�б����������֣���������
			i++;
			pre = p;
			p = p->next;
		}
	}
	printf("\n");
	printf("���������ĺ�����%d��\n", p->id);
}

//5.��ʾ���
void show_tail() {
	printf("\n");
	int i = 0;
	while (i != 110) {
		printf("*");
		i++;
	}
	printf("\n\n");
}