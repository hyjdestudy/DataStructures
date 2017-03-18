#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;  //定义数据域存整数
#define Err_IllegalPos -1;  //非法参数或位置

//定义单链表结点结构
typedef struct LinkNode {
	ElemType data;
	struct LinkNode *next;
}LinkNode;

//初始化单链表
int init_linklist(LinkNode *L) {
	if (!L) {
		printf("无效链表！\n");
		return Err_IllegalPos;
	}
	L->next = NULL;  //初始化头指针，头指针的next指向NULL
	return 1;
}

//清空单链表
int clear_linklist(LinkNode *L) {
	if (!L) {
		printf("无效链表！\n");
		return Err_IllegalPos;
	}
	/*
	清空单链表就是把除头结点以外的所有结点空间释放，
	并将头结点的指针域置为空
	*/
	LinkNode *p = L->next;  //p指针指向第一个结点（头结点的下一个结点）
	LinkNode *q;
	while (p) {
		q = p;
		p = p->next;
		free(q); 
	}
	L->next = NULL;
	return 1;
}

//测试单链表是否为空
bool is_empty(LinkNode *L) {
	if (!L) {
		printf("无效链表！\n");
		return false;
	}
	return L->next == NULL;
}

//求单链表的长度
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

//遍历单链表
void traverse(LinkNode *L) {
	if (!L) {
		printf("无效链表，不能遍历！\n");
		return;
	}
	if (L->next == NULL) {
		printf("单链表为空，没有元素！\n");
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

//向单链表中插入元素
int insert_node(LinkNode *L, int pos, ElemType value) {
	//向单链表L的第pos个位置处，插入data为value的结点，合法位置为1~length+1
	if (!L) {
		printf("无效链表，不能插入元素！\n");
		return Err_IllegalPos;
	}
	//合法单链表，获得其表长，确定合法插入位置
	int length = get_length(L);
	if (pos<1 || pos>length + 1) {
		printf("非法位置，不能插入！\n");
		return Err_IllegalPos;
	}
	int i = 1;
	LinkNode *p = L;  //p指向第i个结点的前驱
	while (i < pos && p) {  //找第pos个结点的前驱节点
		i++;
		p = p->next;
	}
	//做一个新结点
	LinkNode *s = (LinkNode*)malloc(sizeof(LinkNode));
	s->data = value;
	s->next = p->next;
	//把结点s连到前驱p后面
	p->next = s;
	return 1;
}

//删除元素
int delete_node(LinkNode *L,int pos,ElemType *value) {
	if (!L) {
		printf("无效链表，不能删除元素！\n");
		return Err_IllegalPos;
	}
	//删除链表L第pos个位置的元素，把该元素的data存入value里
	int length = get_length(L);
	if (pos<1 || pos>length) {
		printf("非法位置，不能删除该元素！\n");
		return Err_IllegalPos;
	}
	int i = 1;
	LinkNode *p = L;  //p指向要删除结点的前驱
	while (i < pos && p) {
		i++;
		p = p->next;
	}
	LinkNode *q = p->next;  //q指向要删除的结点
	p->next = q->next;
	*value = q->data;
	free(q);
	return 1;
}

//定位元素
int locate_node(LinkNode *L, ElemType value) {
	if (!L) {
		printf("无效链表，不能定位元素！\n");
		return Err_IllegalPos;
	}
	int pos = 1;
	LinkNode *p = L->next;
	while (p && p->data != value) {
		p = p->next;
		pos++;
	}
	if (!p) {
		printf("单链表中无该元素！\n");
		return 0;
	}
	return pos;
}

//获取元素
int get_node(LinkNode *L,int pos,ElemType *value) {  //获取链表L第pos个位置的元素，把它的data存到value里
	if (!L) {
		printf("无效链表，不能获取元素！\n");
		return Err_IllegalPos;
	}
	int length=get_length(L);
	if (pos<1 || pos>length) {
		printf("非法位置，不能获取该元素！\n");
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

//创建单链表（尾插法，链表元素顺序和数据输入顺序一致）
int create_linklist_rear(LinkNode *L,int num) {
	//使用尾插法建立单链表，一共有num个元素，都由用户输入
	if (!L) {
		printf("无效地址，不能用尾插法创建单链表！\n");
		return Err_IllegalPos;
	}	
	printf("正在使用尾插法建立链表\n");
	LinkNode *r = L;  //用r去遍历链表，r为尾指针，使用尾插法建立单链表需要尾指针时刻指向单链表最末位置
	LinkNode *p;  //用p去生成新结点
	int i = 1;
	for (i = 1; i <= num; i++) {
		p = (LinkNode*)malloc(sizeof(LinkNode));
		printf("请输入第%d个结点的值：",i);
		scanf_s("%d", &(p->data));
		p->next = NULL;  //新结点p做好了
		r->next = p;  //把p连到单链表表尾
		r = p;  //更新尾指针，让r时刻指向单链表表尾
	}
	return 1;
}

//创建单链表（头插法，链表元素顺序和数据输入顺序相反）
int create_linklist_head(LinkNode *L,int num) {
	if (!L) {
		printf("无效地址，不能用头插法创建单链表！\n");
		return Err_IllegalPos;
	}
	printf("正在使用头插法建立链表\n");
	LinkNode *p=L;  //用p指向链表的头结点L
	LinkNode *q;  //q用于生成新结点
	int i = 1;
	for (i = 1; i <= num; i++) {
		q = (LinkNode*)malloc(sizeof(LinkNode));
		printf("请输入第%d个结点的值：",i);
		scanf_s("%d",&(q->data));
		q->next = p->next;  //新结点q做好了
		p->next = q;  //把新结点q插到链表头部
	}
	return 1;
}

//销毁单链表
int destroy_linklist(LinkNode *L) {
	/*
	由于单链表的结点空间是动态申请和分配的，所以程序结束后要释放这些结点所占据的空间。
	销毁单链表就是删除所有结点，并从头结点开始逐一释放各结点所占据的空间
	*/
	if (!L) {
		printf("无效地址，不能销毁该单链表！\n");
		return Err_IllegalPos;
	}
	LinkNode *p;  //p用于指向要释放的内存
	while (L) {
		p = L;
		L = p->next;
		free(p);
	}
	return 1;
}

//查看线性表基本信息
void show_list_infor(LinkNode *L) {
	printf("\t--单链表详细信息--\n");
	bool flag = is_empty(L);
	printf("单链表状态：%s\t",flag?"单链表为空！":"单链表不空");
	printf("单链表长度：%d\n",get_length(L));
	printf("单链表元素：\n");
	traverse(L);
	printf("\n");
}

//主函数
int main() {
	int n = 0;  //单链表元素个数
	ElemType e;  //要插入或查找的元素
	ElemType *v = (ElemType*)malloc(sizeof(ElemType));  //存储被删除元素、要获得元素的值
	int p = 1;  //位置参数
	int result = 0;  //接收返回结果
	char ch ='n';  //用户输入，用于确定是否销毁单链表

	LinkNode *my_list_1 = (LinkNode*)malloc(sizeof(LinkNode));
	//初始化一个单链表
	init_linklist(my_list_1);

	do {
		printf("请输入链表指定的元素个数：");
		scanf_s("%d", &n);
		if (n < 0)
			printf("元素个数需大于零！\n");
	} while (n<0);
	printf("\n");

	//利用尾插法建立单链表my_list_1
	result=create_linklist_rear(my_list_1,n);
	printf("\n");
	//利用头插法建立单链表my_list_1
	//result=create_linklist_head(my_list_1, n);
	//遍历单链表1
	show_list_infor(my_list_1);
	
	//向线性表中插入元素
	printf("请输入要插入的位置：");
	scanf_s("%d",&p);
	printf("请输入要插入的元素值：");
	scanf_s("%d",&e);
	result=insert_node(my_list_1,p,e);
	traverse(my_list_1);

	//删除指定元素
	printf("请输入要删除元素的位置：");
	scanf_s("%d", &p);
	result=delete_node(my_list_1,p,v);
	if (result > 0) {  //成功删除
		printf("被删除的元素为：%d\n", *v);
	}	
	traverse(my_list_1);

	//定位元素
	printf("请输入要查找的元素值：");
	scanf_s("%d",&e);
	result=locate_node(my_list_1,e);
	if (result > 0) {
		printf("元素%d是第%d个元素\n",e,result);
	}
	printf("\n");

	//获取元素
	printf("请输入要获取元素的位置：");
	scanf_s("%d",&p);
	result=get_node(my_list_1,p,v);
	if (result > 0) {
		printf("第%d个元素是：%d\n",p,*v);
	}
	printf("\n");

	//清空单链表
	printf("\t--清空单链表操作--\n");
	show_list_infor(my_list_1);
	printf("即将清空单链表，按‘y’确认清空:");
	scanf_s(" %c", &ch, 1);
	if (ch == 'y') {
		result = clear_linklist(my_list_1);
		if (result > 0) {
			printf("您已成功清空该链表，单链表信息如下：\n");
			show_list_infor(my_list_1);
		}
	}
	else {
		printf("您未执行清空操作，单链表信息如下：\n");
		show_list_infor(my_list_1);
	}
	
	//销毁链表
	printf("\t--销毁单链表操作--\n");
	show_list_infor(my_list_1);
	printf("即将销毁单链表，按‘y’确认销毁:");
	scanf_s(" %c", &ch,1);           
	/**********
	这里一定注意，输入格式为" %c"，"%"前面有个空格，
	是为了过滤上次输入的回车
	***********/
	if (ch == 'y') {
		result = destroy_linklist(my_list_1);
		if (result > 0) {
			printf("您已成功销毁该链表！\n");
		}
	}
	else {
		printf("您未执行销毁操作，单链表信息如下：\n");
		show_list_infor(my_list_1);
	}
	printf("\n");
	system("pause");
	return 0;
}