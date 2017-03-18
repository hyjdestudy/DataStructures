#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;  //���������������
#define Err_IllegalPos -1;  //�Ƿ�������λ��

//���嵥������ṹ
typedef struct LinkNode {
	ElemType data;
	struct LinkNode *next;
}LinkNode;

//��ʼ��������
int init_linklist(LinkNode *L) {
	if (!L) {
		printf("��Ч����\n");
		return Err_IllegalPos;
	}
	L->next = NULL;  //��ʼ��ͷָ�룬ͷָ���nextָ��NULL
	return 1;
}

//��յ�����
int clear_linklist(LinkNode *L) {
	if (!L) {
		printf("��Ч����\n");
		return Err_IllegalPos;
	}
	/*
	��յ�������ǰѳ�ͷ�����������н��ռ��ͷţ�
	����ͷ����ָ������Ϊ��
	*/
	LinkNode *p = L->next;  //pָ��ָ���һ����㣨ͷ������һ����㣩
	LinkNode *q;
	while (p) {
		q = p;
		p = p->next;
		free(q); 
	}
	L->next = NULL;
	return 1;
}

//���Ե������Ƿ�Ϊ��
bool is_empty(LinkNode *L) {
	if (!L) {
		printf("��Ч����\n");
		return false;
	}
	return L->next == NULL;
}

//������ĳ���
int get_length(LinkNode *L) {
	if (!L) {
	}
	int count = 0;
	LinkNode *p = L->next;
	while (p) {
		count++;
		p = p->next;
	}
	return count;
}

//����������
void traverse(LinkNode *L) {
	if (!L) {
		printf("��Ч�������ܱ�����\n");
		return;
	}
	if (L->next == NULL) {
		printf("������Ϊ�գ�û��Ԫ�أ�\n");
		return;
	}
	LinkNode *p = L->next;
	int count = 0;
	while (p) {
		printf("%d\t",p->data);
		p = p->next;
		if ((count+1) % 10 == 0) {
			printf("\n");
		}
		count++;
	}
	printf("\n");
}

//�������в���Ԫ��
int insert_node(LinkNode *L, int pos, ElemType value) {
	//������L�ĵ�pos��λ�ô�������dataΪvalue�Ľ�㣬�Ϸ�λ��Ϊ1~length+1
	if (!L) {
		printf("��Ч�������ܲ���Ԫ�أ�\n");
		return Err_IllegalPos;
	}
	//�Ϸ���������������ȷ���Ϸ�����λ��
	int length = get_length(L);
	if (pos<1 || pos>length + 1) {
		printf("�Ƿ�λ�ã����ܲ��룡\n");
		return Err_IllegalPos;
	}
	int i = 1;
	LinkNode *p = L;  //pָ���i������ǰ��
	while (i < pos && p) {  //�ҵ�pos������ǰ���ڵ�
		i++;
		p = p->next;
	}
	//��һ���½��
	LinkNode *s = (LinkNode*)malloc(sizeof(LinkNode));
	s->data = value;
	s->next = p->next;
	//�ѽ��s����ǰ��p����
	p->next = s;
	return 1;
}

//ɾ��Ԫ��
int delete_node(LinkNode *L,int pos,ElemType *value) {
	if (!L) {
		printf("��Ч��������ɾ��Ԫ�أ�\n");
		return Err_IllegalPos;
	}
	//ɾ������L��pos��λ�õ�Ԫ�أ��Ѹ�Ԫ�ص�data����value��
	int length = get_length(L);
	if (pos<1 || pos>length) {
		printf("�Ƿ�λ�ã�����ɾ����Ԫ�أ�\n");
		return Err_IllegalPos;
	}
	int i = 1;
	LinkNode *p = L;  //pָ��Ҫɾ������ǰ��
	while (i < pos && p) {
		i++;
		p = p->next;
	}
	LinkNode *q = p->next;  //qָ��Ҫɾ���Ľ��
	p->next = q->next;
	*value = q->data;
	free(q);
	return 1;
}

//��λԪ��
int locate_node(LinkNode *L, ElemType value) {
	if (!L) {
		printf("��Ч�������ܶ�λԪ�أ�\n");
		return Err_IllegalPos;
	}
	int pos = 1;
	LinkNode *p = L->next;
	while (p && p->data != value) {
		p = p->next;
		pos++;
	}
	if (!p) {
		printf("���������޸�Ԫ�أ�\n");
		return 0;
	}
	return pos;
}

//��ȡԪ��
int get_node(LinkNode *L,int pos,ElemType *value) {  //��ȡ����L��pos��λ�õ�Ԫ�أ�������data�浽value��
	if (!L) {
		printf("��Ч�������ܻ�ȡԪ�أ�\n");
		return Err_IllegalPos;
	}
	int length=get_length(L);
	if (pos<1 || pos>length) {
		printf("�Ƿ�λ�ã����ܻ�ȡ��Ԫ�أ�\n");
		return Err_IllegalPos;
	}
	int i = 1;
	LinkNode *p = L->next;
	while (i < pos) {
		i++;
		p = p->next;
	}
	*value = p->data;
	return 1;
}

//����������β�巨������Ԫ��˳�����������˳��һ�£�
int create_linklist_rear(LinkNode *L,int num) {
	//ʹ��β�巨����������һ����num��Ԫ�أ������û�����
	if (!L) {
		printf("��Ч��ַ��������β�巨����������\n");
		return Err_IllegalPos;
	}	
	printf("����ʹ��β�巨��������\n");
	LinkNode *r = L;  //��rȥ��������rΪβָ�룬ʹ��β�巨������������Ҫβָ��ʱ��ָ��������ĩλ��
	LinkNode *p;  //��pȥ�����½��
	int i = 1;
	for (i = 1; i <= num; i++) {
		p = (LinkNode*)malloc(sizeof(LinkNode));
		printf("�������%d������ֵ��",i);
		scanf_s("%d", &(p->data));
		p->next = NULL;  //�½��p������
		r->next = p;  //��p�����������β
		r = p;  //����βָ�룬��rʱ��ָ�������β
	}
	return 1;
}

//����������ͷ�巨������Ԫ��˳�����������˳���෴��
int create_linklist_head(LinkNode *L,int num) {
	if (!L) {
		printf("��Ч��ַ��������ͷ�巨����������\n");
		return Err_IllegalPos;
	}
	printf("����ʹ��ͷ�巨��������\n");
	LinkNode *p=L;  //��pָ�������ͷ���L
	LinkNode *q;  //q���������½��
	int i = 1;
	for (i = 1; i <= num; i++) {
		q = (LinkNode*)malloc(sizeof(LinkNode));
		printf("�������%d������ֵ��",i);
		scanf_s("%d",&(q->data));
		q->next = p->next;  //�½��q������
		p->next = q;  //���½��q�嵽����ͷ��
	}
	return 1;
}

//���ٵ�����
int destroy_linklist(LinkNode *L) {
	/*
	���ڵ�����Ľ��ռ��Ƕ�̬����ͷ���ģ����Գ��������Ҫ�ͷ���Щ�����ռ�ݵĿռ䡣
	���ٵ��������ɾ�����н�㣬����ͷ��㿪ʼ��һ�ͷŸ������ռ�ݵĿռ�
	*/
	if (!L) {
		printf("��Ч��ַ���������ٸõ�����\n");
		return Err_IllegalPos;
	}
	LinkNode *p;  //p����ָ��Ҫ�ͷŵ��ڴ�
	while (L) {
		p = L;
		L = p->next;
		free(p);
	}
	return 1;
}

//�鿴���Ա������Ϣ
void show_list_infor(LinkNode *L) {
	printf("\t--��������ϸ��Ϣ--\n");
	bool flag = is_empty(L);
	printf("������״̬��%s\t",flag?"������Ϊ�գ�":"��������");
	printf("�������ȣ�%d\n",get_length(L));
	printf("������Ԫ�أ�\n");
	traverse(L);
	printf("\n");
}

//������
int main() {
	int n = 0;  //������Ԫ�ظ���
	ElemType e;  //Ҫ�������ҵ�Ԫ��
	ElemType *v = (ElemType*)malloc(sizeof(ElemType));  //�洢��ɾ��Ԫ�ء�Ҫ���Ԫ�ص�ֵ
	int p = 1;  //λ�ò���
	int result = 0;  //���շ��ؽ��
	char ch ='n';  //�û����룬����ȷ���Ƿ����ٵ�����

	LinkNode *my_list_1 = (LinkNode*)malloc(sizeof(LinkNode));
	//��ʼ��һ��������
	init_linklist(my_list_1);

	do {
		printf("����������ָ����Ԫ�ظ�����");
		scanf_s("%d", &n);
		if (n < 0)
			printf("Ԫ�ظ���������㣡\n");
	} while (n<0);
	printf("\n");

	//����β�巨����������my_list_1
	result=create_linklist_rear(my_list_1,n);
	printf("\n");
	//����ͷ�巨����������my_list_1
	//result=create_linklist_head(my_list_1, n);
	//����������1
	show_list_infor(my_list_1);
	
	//�����Ա��в���Ԫ��
	printf("������Ҫ�����λ�ã�");
	scanf_s("%d",&p);
	printf("������Ҫ�����Ԫ��ֵ��");
	scanf_s("%d",&e);
	result=insert_node(my_list_1,p,e);
	traverse(my_list_1);

	//ɾ��ָ��Ԫ��
	printf("������Ҫɾ��Ԫ�ص�λ�ã�");
	scanf_s("%d", &p);
	result=delete_node(my_list_1,p,v);
	if (result > 0) {  //�ɹ�ɾ��
		printf("��ɾ����Ԫ��Ϊ��%d\n", *v);
	}	
	traverse(my_list_1);

	//��λԪ��
	printf("������Ҫ���ҵ�Ԫ��ֵ��");
	scanf_s("%d",&e);
	result=locate_node(my_list_1,e);
	if (result > 0) {
		printf("Ԫ��%d�ǵ�%d��Ԫ��\n",e,result);
	}
	printf("\n");

	//��ȡԪ��
	printf("������Ҫ��ȡԪ�ص�λ�ã�");
	scanf_s("%d",&p);
	result=get_node(my_list_1,p,v);
	if (result > 0) {
		printf("��%d��Ԫ���ǣ�%d\n",p,*v);
	}
	printf("\n");

	//��յ�����
	printf("\t--��յ��������--\n");
	show_list_infor(my_list_1);
	printf("������յ���������y��ȷ�����:");
	scanf_s(" %c", &ch, 1);
	if (ch == 'y') {
		result = clear_linklist(my_list_1);
		if (result > 0) {
			printf("���ѳɹ���ո�������������Ϣ���£�\n");
			show_list_infor(my_list_1);
		}
	}
	else {
		printf("��δִ����ղ�������������Ϣ���£�\n");
		show_list_infor(my_list_1);
	}
	
	//��������
	printf("\t--���ٵ��������--\n");
	show_list_infor(my_list_1);
	printf("�������ٵ���������y��ȷ������:");
	scanf_s(" %c", &ch,1);           
	/**********
	����һ��ע�⣬�����ʽΪ" %c"��"%"ǰ���и��ո�
	��Ϊ�˹����ϴ�����Ļس�
	***********/
	if (ch == 'y') {
		result = destroy_linklist(my_list_1);
		if (result > 0) {
			printf("���ѳɹ����ٸ�����\n");
		}
	}
	else {
		printf("��δִ�����ٲ�������������Ϣ���£�\n");
		show_list_infor(my_list_1);
	}
	printf("\n");
	system("pause");
	return 0;
}