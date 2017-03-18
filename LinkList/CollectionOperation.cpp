/*
���õ�����ʵ�ּ��ϵĲ������������
�������Ԫ��Ϊ�ַ���
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR_INVALIDPARAM -1  //��Ч����
#define ERR_ILLEGALPOS -2  //�Ƿ�λ��
#define ERR_MEMORY -3  //�ڴ�����쳣
#define ELEM_SIZE 11  //������Ԫ�ش�С
typedef char ElemType;  //�������Ԫ��Ϊ�ַ���

//����Ԫ�ؽ�㣬������Nodeָ���ʾ
typedef struct Node{
	ElemType *data;  //�������Ԫ��Ϊ�ַ���
	struct Node *next;  //ͨ����Ԫ�ص�nextָ�룬��һ����������һ��������
}Node;

/*���ܺ�������*/
int init_set(Node *S);  //1.��ʼ������
int clear_set(Node *S);  //2.��ռ���
bool is_empty_set(Node *S);  //3.���Լ����Ƿ�Ϊ�ռ�
int get_size(Node *S);  //4.�󼯺ϵĴ�С
void traverse_set(Node *S);  //5.��������
void show_set_infor(Node *S);  //6.��ʾ���ϻ�����Ϣ
int locate_elem(Node *S, ElemType *value);  //7.ȷ���������Ƿ����ĳԪ�أ��û���������ʱ���ж�    ��һ��ע�������Ͷ��壬����Ҫһ�£���
int add_elem(Node *S, ElemType *value);  //8.�򼯺������Ԫ�أ��������β�巨��
int delete_elem(Node *S, ElemType *value);   //9.ɾ������Ԫ��
int get_elem(Node *S, int pos, ElemType *value);  //10.ȡ�ü����е�ĳԪ��
int create_set(Node *S);  //11.��������
int destroy_set(Node *S);  //12.���ټ���						  
int union_op(Node *SA, Node *SB, Node *UC);  //13.���ϵĲ����㣺�󼯺�SA��SB�Ĳ���UC
int intersect_op(Node *A, Node *B, Node *C);  //14.���ϵĽ����� ���󼯺�A,B�Ľ���C
int except_op(Node *A, Node *B, Node *C);  //15.���ϵĲ����㣺�󼯺�A,B�ĲC
void show_tail();  //16.��ʾ���

//������
int main() {
	int result = 0;  //����ִ�н��״̬
	//3�����ϣ�A��BΪԴ��������CΪ���
	Node *A= (Node*)malloc(sizeof(Node));
	result = init_set(A);
	if (result != 1) {
		printf("��ʼ������Aʧ�ܣ�\n");
		return ERR_MEMORY;
	}
	Node *B= (Node*)malloc(sizeof(Node));
	result = init_set(B);
	if (result != 1) {
		printf("��ʼ������Bʧ�ܣ�\n");
		return ERR_MEMORY;
	}
	Node *C= (Node*)malloc(sizeof(Node));
	result = init_set(C);
	if (result != 1) {
		printf("��ʼ������Cʧ�ܣ�\n");
		return ERR_MEMORY;
	}
	result = 0;

	int choice = 0;  //�û�����
	char ch;  //�������ջس�

	while (true) {
		printf("\t\t\t\t\t--���ϲ����˵�--\n");
		printf("1.��������A,B\t 2.�鿴����A,B\t 3.��A,B�Ĳ���C\t 4.��A,B�Ľ���C\t 5.��A,B�ĲC\t 6.�˳�����\n");
		printf("���������Ĳ�����");
		scanf_s("%d",&choice);
		ch=getchar();  //���ջس���
		printf("\n");
	
		switch (choice) {
			case 1:  //��������A,B,C
				printf("\t\t\t\t\t--��������A,B--\n");
				printf("**��������A��ÿ��Ԫ�����10���ַ�������'#'�������룩**\n");
				//A = (Node*)malloc(sizeof(Node));
				result = create_set(A);
				if (result == 1) {
					printf("�ɹ���������A��\n");
				}
				if (result < 0) {
					printf("��������Aʧ�ܣ��������˳���\n");
					system("pause");
					return 0;
				}
				printf("\n");

				printf("**��������B��ÿ��Ԫ�����10���ַ�������'#'�������룩**\n");
				//B = (Node*)malloc(sizeof(Node));
				result = create_set(B);
				if (result == 1) {
					printf("�ɹ���������B��\n");
				}
				if (result < 0) {
					printf("��������Bʧ�ܣ��������˳���\n");
					system("pause");
					return 0;
				}

				//��ʼ���������C
				//C = (Node*)malloc(sizeof(Node));
				result=init_set(C);
				if (result < 0) {
					printf("��ʼ������Cʧ�ܣ��������˳���\n");
					system("pause");
					return 0;
				}
				show_tail();
				break;

			case 2:  //�鿴������Ϣ
				printf("\t\t\t\t\t--�鿴����A,B--\n");
				printf("����A:\n");
				show_set_infor(A);
				printf("����B:\n");
				show_set_infor(B);
				show_tail();
				break;

			case 3:  //�󼯺�A,B�Ĳ���C
				printf("\t\t\t\t\t--�󼯺�A,B�Ĳ���C--\n");
				//��ռ���C
				result = clear_set(C);
				if (result < 0) {
					printf("��ռ���Cʧ�ܣ��������˳���\n");
					system("pause");
					return 0;
				}
				result=union_op(A, B, C);
				if (result < 0) {
					printf("�󲢼�ʧ�ܣ��������˳���\n");
					system("pause");
					return 0;
				}
				printf("A,B�Ĳ���C��\n");
				show_set_infor(C);
				show_tail();
				break;

			case 4:  //��A,B�Ľ���C
				printf("\t\t\t\t\t--�󼯺�A,B�Ľ���C--\n");
				//��ռ���C
				result = clear_set(C);
				if (result < 0) {
					printf("��ռ���Cʧ�ܣ��������˳���\n");
					system("pause");
					return 0;
				}
				result=intersect_op(A, B, C);
				if (result < 0) {
					printf("�󽻼�ʧ�ܣ��������˳���\n");
					system("pause");
					return 0;
				}
				printf("A,B�Ľ���C��\n");
				show_set_infor(C);
				show_tail();
				break;

			case 5:  //��A,B�ĲC			
				printf("\t\t\t\t\t--�󼯺�A,B�ĲC--\n");
				//��ռ���C
				result = clear_set(C);
				if (result < 0) {
					printf("��ռ���Cʧ�ܣ��������˳���\n");
					system("pause");
					return 0;
				}
				result=except_op(A, B, C);
				if (result < 0) {
					printf("�󽻼�ʧ�ܣ��������˳���\n");
					system("pause");
					return 0;
				}
				printf("A,B�ĲC��\n");
				show_set_infor(C);
				show_tail();
				break;

			case 6:  //�����˳�
				printf("\t\t\t\t\t--�������˳�--\n");
				destroy_set(A);
				destroy_set(B);
				destroy_set(C);
				printf("�����ټ���A,B,C�����Ѱ�ȫ�˳���\n");
				system("pause");
				return 0;
				break;
			default:
				printf("\t\t\t\t\t--ѡ�����--\n");
				printf("�˵��������������ѡ��\n");
				show_tail();
		}
	}

	printf("������������������\n");
	system("pause");
	return 0;
}

/*
���ܺ�������
*/
//1.��ʼ������
int init_set(Node *S) {
	if (!S) {
		printf("��Ч���ϣ����ܳ�ʼ�����ϣ�\n");
		return ERR_INVALIDPARAM;
	}
	S->next = NULL;
	return 1;
}

//2.��ռ���
int clear_set(Node *S) {
	if (!S) {
		printf("��Ч���ϣ�������ռ��ϣ�\n");
		return ERR_INVALIDPARAM;
	}
	Node *p = S->next;  //����ͷ����⣬ʣ�µĽ��˳������
	Node *q;  //q�����ͷŽ��
	while (p) {
		q = p;
		p = p->next;
		free(q);
	}
	S->next = NULL;
	return 1;
}

//3.���Լ����Ƿ�Ϊ�ռ�
bool is_empty_set(Node *S) {
	if (!S) {
		printf("��Ч���ϣ����ܼ���Ƿ�ռ���\n");  //�涨����Ч������Ϊ�ռ�
		return true;
	}
	return S->next == NULL;
}

//4.�󼯺ϵĴ�С
int get_size(Node *S) {
	if (!S) {
		printf("��Ч���ϣ����ܻ�ȡ���ϴ�С��\n");
		return ERR_INVALIDPARAM;
	}
	int count = 0;
	Node *p = S->next;
	while (p) {
		count++;
		p = p->next;
	}
	return count;
}

//5.��������
void traverse_set(Node *S) {
	if (!S) {
		printf("��Ч���ϣ����ܱ������ϣ�\n");
		return;
	}
	Node *p = S->next;
	int i = 0;
	printf("����Ԫ��Ϊ��\n");
	while (p) {
		printf("%s\t",p->data);
		if ((i + 1) % 10 == 0) {
			printf("\n");
		}
		p = p->next;
		i++;
	}
	printf("\n");
}

//6.��ʾ���ϻ�����Ϣ
void show_set_infor(Node *S) {
	if (!S) {
		printf("��Ч���ϣ����ܲ鿴������Ϣ��\n");
		return;
	}
	int size = get_size(S);
	printf("���ϴ�СΪ��%d\n", size);
	if (size > 0)
		traverse_set(S);
	else
		printf("��ǰ����Ϊ�ռ���\n");
}

//7.ȷ��ĳԪ���ڼ����е�λ��
int locate_elem(Node *S, ElemType *value) {
	if (!S) {
		printf("��Ч���ϣ������ڸü���������Ԫ�أ�\n");
		return ERR_INVALIDPARAM;
	}
	int pos = 1;  //һ��ע�⣬����Ԫ��㿪ʼ�Ƚϣ�������ͷ��㣬��д��pos=0��
	Node *p = S->next;
	while (p && strcmp(p->data, value) != 0) {
		p = p->next;
		pos++;
	}
	if (!p) {
		pos = 0;  //������δ���ҵ�Ԫ��value
	}
	return pos;
}

//8.�򼯺������Ԫ�أ��������β�巨��
int add_elem(Node *S,ElemType *value) {
	if (!S) {
		printf("��Ч���ϣ�������ü��������Ԫ�أ�\n");
		return ERR_INVALIDPARAM;
	}
	Node *r = S;  //rָ��ʱ��ָ��S��ĩβ
	while (r->next) {  //��S�����һ��Ԫ��
		r = r->next;
	}
	//���½��
	Node *n = (Node*)malloc(sizeof(Node));
	if (!n) {
		printf("�ڴ������󣬲��ܽ����½�㣡\n");
		return ERR_MEMORY;
	}
	n->data = (ElemType*)malloc(sizeof(ElemType)*ELEM_SIZE);
	if (!(n->data)) {
		printf("�ڴ������󣬲��������������洢���ݣ�\n");
		return ERR_MEMORY;
	}
	strcpy_s(n->data,ELEM_SIZE,value);
	n->next = NULL;
	//���½��ӵ�������
	r->next = n;
	r = n;
	return 1;
}

//9.ɾ������S��ָ����Ԫ��target
int delete_elem(Node *S,ElemType *target) {
	if (!S) {
		printf("��Ч���ϣ����ܴӸü�����ɾ��Ԫ�أ�\n");
		return ERR_INVALIDPARAM;
	}
	Node *p,*q;
	int pos = locate_elem(S, target);
	if (pos > 0) {  //�ҵ���Ԫ����
		int i = 1;  //��iȥ�ҵ�pos��Ԫ��
		p = S;  //p������i��ǰ��	���	
		while (i < pos && p) {
			i++;
			p = p->next;
		}
		//�ҵ���pos��Ԫ����
		q = p->next;  //��qָ��Ҫɾ���Ľ��
		p->next = q->next;
		free(q);
		printf("ɾ��Ԫ��%s�ɹ���\n", target);
		return 1;
	}
	else {
		printf("�ü����в�����Ԫ��%s������ִ��ɾ��������\n",target);
	}
	return 0;
}

//10.ȡ�ü����е�ĳԪ��
int get_elem(Node *S, int pos, ElemType *value) {
	if (!S) {
		printf("��Ч���ϣ����ܴӸü����л�ȡԪ�أ�\n");
		return ERR_INVALIDPARAM;
	}
	int size = get_size(S);
	if (pos<1 || pos>size) {
		printf("�Ƿ����������ܻ�ø�λ��Ԫ�أ�\n");
		return ERR_ILLEGALPOS;
	}
	int i = 1;
	Node *p = S->next;
	while (i < pos && p) {
		i++;
		p = p->next;
	}
	strcpy_s(value,ELEM_SIZE,p->data);
	return 1;
}

//11.��������
/*
��ָ�����ϴ�С���û������Ԫ�أ��͹�����ļ��ϣ��û�����'#'��ʾ�������
����add_elem�����Ԫ��
*/
int create_set(Node *S) {
	if (!S) {
		printf("��Ч���ϵ�ַ�����ܴ������ϣ�\n");
		return ERR_INVALIDPARAM;
	}
	if (clear_set(S)!=1) {  //��������ǰ���Ȱ���ǰ��Ԫ��ȫ���
		printf("�޷������ʷԪ�أ���������ʧ�ܣ�");
		return ERR_INVALIDPARAM;
	}
	Node *r = S;  //rָ�򼯺ϵ�ĩβ
	ElemType *elem;  //���ڽ����û������Ԫ��
	int count = 1;  //���ڼ�¼�û����������Ԫ��
	int status = 0;  //���ڽ��ղ����ķ���״̬
	int pos = 0;  //���ڽ��պ������ص�Ԫ��λ��
	while (true) {
		printf("�������%d��Ԫ�أ�\n",count++);
		elem = (ElemType*)malloc(sizeof(ElemType)*ELEM_SIZE);  //Ϊ������������׼���ռ�
		if (!elem) {
			printf("���û��������ռ�ʧ�ܣ�\n");
			return ERR_MEMORY;
		}
		gets_s(elem,ELEM_SIZE);  //�����û�����
		if (strcmp(elem, "#") == 0) {
			printf("�������������\n");
			break;
		}
		pos =locate_elem(S,elem);  //�鿴�û������elemԪ���Ƿ��Ѱ����ڼ���S��
		if (pos==0) {  //����S�в�����Ԫ��elem
			add_elem(S,elem);  //��Ԫ��elem��ӵ�����S��
		}
	}
	return 1;
}

//12.���ټ��ϣ��ͷ����н�㣬����ͷ��㣩
int destroy_set(Node *S) {
	if (!S) {
		printf("��Ч���ϵ�ַ���������٣�\n");
		return ERR_INVALIDPARAM;
	}
	Node *p=S;  //pָ�򼯺Ͻ�㣬����ͷ�
	while (S) {
		p = S;
		S = S->next;
		free(p);
	}
	return 1;
}

//13.���ϵĲ�����
int union_op(Node *SA,Node *SB, Node *UC) {  //�󼯺�SA��SB�Ĳ���UC
	if (!SA || !SB || !UC) {
		printf("������Ч���ϣ����ܽ��в����㣡\n");
		return ERR_INVALIDPARAM;
	}

	Node *p, *q;  //p��q���ڱ�������SA��SB
	ElemType *value;  //value���ڴ������ֵ
	int result = 0;  //���ղ����ķ���ֵ
	int pos = 0;  //����Ԫ�ص�����λ��

	p = SA->next;
	//�Ȱ���������A���Ƹ�C��β�巨��
	while (p) {
		value = (ElemType*)malloc(sizeof(ElemType)*ELEM_SIZE);  //����ô�value�Ŀռ�
		strcpy_s(value, sizeof(ElemType)*ELEM_SIZE,p->data);  //��value��ֵ
		result=add_elem(UC,value);  //��valueΪdataֵ������UC������
		if (result != 1) {  //����ʧ��
			printf("�󲢼������г����쳣��\n");
			return ERR_MEMORY;
		}
		p = p->next;
	}

	//�ٱ�������B���Ѳ���C�е���ӵ�C��
	q = SB->next;
	while (q) {
		pos=locate_elem(UC,q->data);
		if (pos == 0) {  //û���ҵ���Ԫ��
			value = (ElemType*)malloc(sizeof(ElemType)*ELEM_SIZE);
			strcpy_s(value,sizeof(ElemType)*ELEM_SIZE,q->data);
			result=add_elem(UC,value);
			if (result != 1) {  //����ʧ��
				printf("�󲢼������г����쳣��\n");
				return ERR_MEMORY;
			}
		}
		q = q->next;
	}
	return 1;
}

//14.���ϵĽ�����
int intersect_op(Node *A, Node *B, Node *C) {  //�󼯺�A,B�Ľ���C������A��ͬʱ���B����A����B���ӵ�C�
	if (!A || !B || !C) {
		printf("������Ч���ϣ����ܽ��н����㣡\n");
		return ERR_INVALIDPARAM;
	}

	Node *p;  //���ڱ�������A��B
	ElemType *value;  //�����ݴ�data
	int pos = 0;  //���ڽ��շ��ص�Ԫ�ص�ַ
	int result = 0;  //���ڽ��ղ�����ִ�н��

	p = A->next;  
	while (p) {  //����A
		pos = locate_elem(B, p->data);  //�ж�A���data�Ƿ���B��
		if (pos>0) {  //data��A��B
			value = (ElemType*)malloc(sizeof(ElemType)*ELEM_SIZE);  //��value�ܴ�data
			strcpy_s(value,sizeof(ElemType)*ELEM_SIZE,p->data);  //��data�浽value��
			result=add_elem(C,value);
			if (result != 1) {  //����ʧ��
				printf("�󽻼������г����쳣��\n");
				return ERR_MEMORY;
			}
		}
		p = p->next;
	}
	return 1;
}

//15.���ϵĲ�����
int except_op(Node *A, Node *B, Node *C) {  //�󼯺�A,B�ĲC������A��ͬʱ���B����A�Ҳ���B���ӵ�C�
	if (!A || !B || !C) {
		printf("������Ч���ϣ����ܽ��в����㣡\n");
		return ERR_INVALIDPARAM;
	}
	Node *p;  //���ڱ�������A��B
	ElemType *value;  //�����ݴ�data
	int pos = 0;  //���ڽ��շ��ص�Ԫ�ص�ַ
	int result = 0;  //���ڽ��ղ�����ִ�н��

	p = A->next;
	while (p) {  //����A
		pos = locate_elem(B, p->data);  //�ж�A���data�Ƿ���B��
		if (pos==0) {  //data��A�Ҳ���B
			value = (ElemType*)malloc(sizeof(ElemType)*ELEM_SIZE);  //��value�ܴ�data
			strcpy_s(value, sizeof(ElemType)*ELEM_SIZE, p->data);  //��data�浽value��
			result = add_elem(C, value);
			if (result != 1) {  //����ʧ��
				printf("�󽻼������г����쳣��\n");
				return ERR_MEMORY;
			}
		}
		p = p->next;
	}
	return 1;
}

//16.��ʾ���
void show_tail() {
	printf("\n");
	printf("********************************************************************************************\n");
	printf("\n");
}