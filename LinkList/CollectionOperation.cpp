/*
利用单链表实现集合的并集、交集、差集
集合里的元素为字符串
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR_INVALIDPARAM -1  //无效参数
#define ERR_ILLEGALPOS -2  //非法位置
#define ERR_MEMORY -3  //内存分配异常
#define ELEM_SIZE 11  //集合里元素大小
typedef char ElemType;  //集合里的元素为字符串

//定义元素结点，集合用Node指针表示
typedef struct Node{
	ElemType *data;  //集合里的元素为字符串
	struct Node *next;  //通过各元素的next指针，把一个集合做成一个单链表
}Node;

/*功能函数声明*/
int init_set(Node *S);  //1.初始化集合
int clear_set(Node *S);  //2.清空集合
bool is_empty_set(Node *S);  //3.测试集合是否为空集
int get_size(Node *S);  //4.求集合的大小
void traverse_set(Node *S);  //5.遍历集合
void show_set_infor(Node *S);  //6.显示集合基本信息
int locate_elem(Node *S, ElemType *value);  //7.确定集合中是否包含某元素，用户输入数据时就判断    （一定注意声明和定义，参数要一致！）
int add_elem(Node *S, ElemType *value);  //8.向集合中添加元素（这里采用尾插法）
int delete_elem(Node *S, ElemType *value);   //9.删除集合元素
int get_elem(Node *S, int pos, ElemType *value);  //10.取得集合中的某元素
int create_set(Node *S);  //11.创建集合
int destroy_set(Node *S);  //12.销毁集合						  
int union_op(Node *SA, Node *SB, Node *UC);  //13.集合的并运算：求集合SA、SB的并集UC
int intersect_op(Node *A, Node *B, Node *C);  //14.集合的交运算 ：求集合A,B的交集C
int except_op(Node *A, Node *B, Node *C);  //15.集合的差运算：求集合A,B的差集C
void show_tail();  //16.显示外观

//主函数
int main() {
	int result = 0;  //接收执行结果状态
	//3个集合，A和B为源操作数，C为结果
	Node *A= (Node*)malloc(sizeof(Node));
	result = init_set(A);
	if (result != 1) {
		printf("初始化集合A失败！\n");
		return ERR_MEMORY;
	}
	Node *B= (Node*)malloc(sizeof(Node));
	result = init_set(B);
	if (result != 1) {
		printf("初始化集合B失败！\n");
		return ERR_MEMORY;
	}
	Node *C= (Node*)malloc(sizeof(Node));
	result = init_set(C);
	if (result != 1) {
		printf("初始化集合C失败！\n");
		return ERR_MEMORY;
	}
	result = 0;

	int choice = 0;  //用户输入
	char ch;  //用于吸收回车

	while (true) {
		printf("\t\t\t\t\t--集合操作菜单--\n");
		printf("1.创建集合A,B\t 2.查看集合A,B\t 3.求A,B的并集C\t 4.求A,B的交集C\t 5.求A,B的差集C\t 6.退出程序\n");
		printf("请输入您的操作：");
		scanf_s("%d",&choice);
		ch=getchar();  //吸收回车符
		printf("\n");
	
		switch (choice) {
			case 1:  //创建集合A,B,C
				printf("\t\t\t\t\t--创建集合A,B--\n");
				printf("**创建集合A（每个元素最多10个字符，输入'#'结束输入）**\n");
				//A = (Node*)malloc(sizeof(Node));
				result = create_set(A);
				if (result == 1) {
					printf("成功创建集合A！\n");
				}
				if (result < 0) {
					printf("创建集合A失败，程序已退出！\n");
					system("pause");
					return 0;
				}
				printf("\n");

				printf("**创建集合B（每个元素最多10个字符，输入'#'结束输入）**\n");
				//B = (Node*)malloc(sizeof(Node));
				result = create_set(B);
				if (result == 1) {
					printf("成功创建集合B！\n");
				}
				if (result < 0) {
					printf("创建集合B失败，程序已退出！\n");
					system("pause");
					return 0;
				}

				//初始化结果集合C
				//C = (Node*)malloc(sizeof(Node));
				result=init_set(C);
				if (result < 0) {
					printf("初始化集合C失败，程序已退出！\n");
					system("pause");
					return 0;
				}
				show_tail();
				break;

			case 2:  //查看集合信息
				printf("\t\t\t\t\t--查看集合A,B--\n");
				printf("集合A:\n");
				show_set_infor(A);
				printf("集合B:\n");
				show_set_infor(B);
				show_tail();
				break;

			case 3:  //求集合A,B的并集C
				printf("\t\t\t\t\t--求集合A,B的并集C--\n");
				//清空集合C
				result = clear_set(C);
				if (result < 0) {
					printf("清空集合C失败，程序已退出！\n");
					system("pause");
					return 0;
				}
				result=union_op(A, B, C);
				if (result < 0) {
					printf("求并集失败，程序已退出！\n");
					system("pause");
					return 0;
				}
				printf("A,B的并集C：\n");
				show_set_infor(C);
				show_tail();
				break;

			case 4:  //求A,B的交集C
				printf("\t\t\t\t\t--求集合A,B的交集C--\n");
				//清空集合C
				result = clear_set(C);
				if (result < 0) {
					printf("清空集合C失败，程序已退出！\n");
					system("pause");
					return 0;
				}
				result=intersect_op(A, B, C);
				if (result < 0) {
					printf("求交集失败，程序已退出！\n");
					system("pause");
					return 0;
				}
				printf("A,B的交集C：\n");
				show_set_infor(C);
				show_tail();
				break;

			case 5:  //求A,B的差集C			
				printf("\t\t\t\t\t--求集合A,B的差集C--\n");
				//清空集合C
				result = clear_set(C);
				if (result < 0) {
					printf("清空集合C失败，程序已退出！\n");
					system("pause");
					return 0;
				}
				result=except_op(A, B, C);
				if (result < 0) {
					printf("求交集失败，程序已退出！\n");
					system("pause");
					return 0;
				}
				printf("A,B的差集C：\n");
				show_set_infor(C);
				show_tail();
				break;

			case 6:  //程序退出
				printf("\t\t\t\t\t--程序已退出--\n");
				destroy_set(A);
				destroy_set(B);
				destroy_set(C);
				printf("已销毁集合A,B,C，您已安全退出！\n");
				system("pause");
				return 0;
				break;
			default:
				printf("\t\t\t\t\t--选择错误--\n");
				printf("菜单输入错误，请重新选择！\n");
				show_tail();
		}
	}

	printf("从主函数里跳出来了\n");
	system("pause");
	return 0;
}

/*
功能函数定义
*/
//1.初始化集合
int init_set(Node *S) {
	if (!S) {
		printf("无效集合，不能初始化集合！\n");
		return ERR_INVALIDPARAM;
	}
	S->next = NULL;
	return 1;
}

//2.清空集合
int clear_set(Node *S) {
	if (!S) {
		printf("无效集合，不能清空集合！\n");
		return ERR_INVALIDPARAM;
	}
	Node *p = S->next;  //除了头结点外，剩下的结点顺次清理
	Node *q;  //q用于释放结点
	while (p) {
		q = p;
		p = p->next;
		free(q);
	}
	S->next = NULL;
	return 1;
}

//3.测试集合是否为空集
bool is_empty_set(Node *S) {
	if (!S) {
		printf("无效集合，不能检测是否空集！\n");  //规定：无效集合视为空集
		return true;
	}
	return S->next == NULL;
}

//4.求集合的大小
int get_size(Node *S) {
	if (!S) {
		printf("无效集合，不能获取集合大小！\n");
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

//5.遍历集合
void traverse_set(Node *S) {
	if (!S) {
		printf("无效集合，不能遍历集合！\n");
		return;
	}
	Node *p = S->next;
	int i = 0;
	printf("集合元素为：\n");
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

//6.显示集合基本信息
void show_set_infor(Node *S) {
	if (!S) {
		printf("无效集合，不能查看集合信息！\n");
		return;
	}
	int size = get_size(S);
	printf("集合大小为：%d\n", size);
	if (size > 0)
		traverse_set(S);
	else
		printf("当前集合为空集！\n");
}

//7.确定某元素在集合中的位置
int locate_elem(Node *S, ElemType *value) {
	if (!S) {
		printf("无效集合，不能在该集合中搜索元素！\n");
		return ERR_INVALIDPARAM;
	}
	int pos = 1;  //一定注意，从首元结点开始比较，而不是头结点，别写成pos=0了
	Node *p = S->next;
	while (p && strcmp(p->data, value) != 0) {
		p = p->next;
		pos++;
	}
	if (!p) {
		pos = 0;  //集合中未查找到元素value
	}
	return pos;
}

//8.向集合中添加元素（这里采用尾插法）
int add_elem(Node *S,ElemType *value) {
	if (!S) {
		printf("无效集合，不能向该集合中添加元素！\n");
		return ERR_INVALIDPARAM;
	}
	Node *r = S;  //r指针时刻指向S的末尾
	while (r->next) {  //找S的最后一个元素
		r = r->next;
	}
	//做新结点
	Node *n = (Node*)malloc(sizeof(Node));
	if (!n) {
		printf("内存分配错误，不能建立新结点！\n");
		return ERR_MEMORY;
	}
	n->data = (ElemType*)malloc(sizeof(ElemType)*ELEM_SIZE);
	if (!(n->data)) {
		printf("内存分配错误，不能向结点的数据域存储数据！\n");
		return ERR_MEMORY;
	}
	strcpy_s(n->data,ELEM_SIZE,value);
	n->next = NULL;
	//把新结点加到集合里
	r->next = n;
	r = n;
	return 1;
}

//9.删除集合S中指定的元素target
int delete_elem(Node *S,ElemType *target) {
	if (!S) {
		printf("无效集合，不能从该集合中删除元素！\n");
		return ERR_INVALIDPARAM;
	}
	Node *p,*q;
	int pos = locate_elem(S, target);
	if (pos > 0) {  //找到该元素了
		int i = 1;  //用i去找第pos个元素
		p = S;  //p用于找i的前驱	结点	
		while (i < pos && p) {
			i++;
			p = p->next;
		}
		//找到第pos个元素了
		q = p->next;  //用q指向要删除的结点
		p->next = q->next;
		free(q);
		printf("删除元素%s成功！\n", target);
		return 1;
	}
	else {
		printf("该集合中不包含元素%s，不能执行删除操作！\n",target);
	}
	return 0;
}

//10.取得集合中的某元素
int get_elem(Node *S, int pos, ElemType *value) {
	if (!S) {
		printf("无效集合，不能从该集合中获取元素！\n");
		return ERR_INVALIDPARAM;
	}
	int size = get_size(S);
	if (pos<1 || pos>size) {
		printf("非法参数，不能获得该位置元素！\n");
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

//11.创建集合
/*
不指定集合大小，用户输多少元素，就构造多大的集合，用户输入'#'表示输入结束
调用add_elem来添加元素
*/
int create_set(Node *S) {
	if (!S) {
		printf("无效集合地址，不能创建集合！\n");
		return ERR_INVALIDPARAM;
	}
	if (clear_set(S)!=1) {  //创建集合前，先把以前的元素全清空
		printf("无法清空历史元素，创建集合失败！");
		return ERR_INVALIDPARAM;
	}
	Node *r = S;  //r指向集合的末尾
	ElemType *elem;  //用于接收用户输入的元素
	int count = 1;  //用于记录用户已输入多少元素
	int status = 0;  //用于接收操作的返回状态
	int pos = 0;  //用于接收函数返回的元素位置
	while (true) {
		printf("请输入第%d个元素：\n",count++);
		elem = (ElemType*)malloc(sizeof(ElemType)*ELEM_SIZE);  //为接收输入数据准备空间
		if (!elem) {
			printf("给用户输入分配空间失败！\n");
			return ERR_MEMORY;
		}
		gets_s(elem,ELEM_SIZE);  //接收用户输入
		if (strcmp(elem, "#") == 0) {
			printf("数据输入结束！\n");
			break;
		}
		pos =locate_elem(S,elem);  //查看用户输入的elem元素是否已包含在集合S中
		if (pos==0) {  //集合S中不包含元素elem
			add_elem(S,elem);  //把元素elem添加到集合S里
		}
	}
	return 1;
}

//12.销毁集合（释放所有结点，包括头结点）
int destroy_set(Node *S) {
	if (!S) {
		printf("无效集合地址，不能销毁！\n");
		return ERR_INVALIDPARAM;
	}
	Node *p=S;  //p指向集合结点，逐个释放
	while (S) {
		p = S;
		S = S->next;
		free(p);
	}
	return 1;
}

//13.集合的并运算
int union_op(Node *SA,Node *SB, Node *UC) {  //求集合SA、SB的并集UC
	if (!SA || !SB || !UC) {
		printf("存在无效集合，不能进行并运算！\n");
		return ERR_INVALIDPARAM;
	}

	Node *p, *q;  //p、q用于遍历集合SA、SB
	ElemType *value;  //value用于存各结点的值
	int result = 0;  //接收操作的返回值
	int pos = 0;  //接收元素的所在位置

	p = SA->next;
	//先把整个集合A复制给C（尾插法）
	while (p) {
		value = (ElemType*)malloc(sizeof(ElemType)*ELEM_SIZE);  //分配好存value的空间
		strcpy_s(value, sizeof(ElemType)*ELEM_SIZE,p->data);  //给value赋值
		result=add_elem(UC,value);  //以value为data值，插入UC集合中
		if (result != 1) {  //插入失败
			printf("求并集操作中出现异常！\n");
			return ERR_MEMORY;
		}
		p = p->next;
	}

	//再遍历集合B，把不在C中的添加到C里
	q = SB->next;
	while (q) {
		pos=locate_elem(UC,q->data);
		if (pos == 0) {  //没有找到该元素
			value = (ElemType*)malloc(sizeof(ElemType)*ELEM_SIZE);
			strcpy_s(value,sizeof(ElemType)*ELEM_SIZE,q->data);
			result=add_elem(UC,value);
			if (result != 1) {  //插入失败
				printf("求并集操作中出现异常！\n");
				return ERR_MEMORY;
			}
		}
		q = q->next;
	}
	return 1;
}

//14.集合的交运算
int intersect_op(Node *A, Node *B, Node *C) {  //求集合A,B的交集C（遍历A，同时检查B，在A且在B，加到C里）
	if (!A || !B || !C) {
		printf("存在无效集合，不能进行交运算！\n");
		return ERR_INVALIDPARAM;
	}

	Node *p;  //用于遍历集合A和B
	ElemType *value;  //用于暂存data
	int pos = 0;  //用于接收返回的元素地址
	int result = 0;  //用于接收操作的执行结果

	p = A->next;  
	while (p) {  //遍历A
		pos = locate_elem(B, p->data);  //判断A里的data是否在B中
		if (pos>0) {  //data在A且B
			value = (ElemType*)malloc(sizeof(ElemType)*ELEM_SIZE);  //让value能存data
			strcpy_s(value,sizeof(ElemType)*ELEM_SIZE,p->data);  //把data存到value里
			result=add_elem(C,value);
			if (result != 1) {  //插入失败
				printf("求交集操作中出现异常！\n");
				return ERR_MEMORY;
			}
		}
		p = p->next;
	}
	return 1;
}

//15.集合的差运算
int except_op(Node *A, Node *B, Node *C) {  //求集合A,B的差集C（遍历A，同时检查B，在A且不在B，加到C里）
	if (!A || !B || !C) {
		printf("存在无效集合，不能进行差运算！\n");
		return ERR_INVALIDPARAM;
	}
	Node *p;  //用于遍历集合A和B
	ElemType *value;  //用于暂存data
	int pos = 0;  //用于接收返回的元素地址
	int result = 0;  //用于接收操作的执行结果

	p = A->next;
	while (p) {  //遍历A
		pos = locate_elem(B, p->data);  //判断A里的data是否在B中
		if (pos==0) {  //data在A且不在B
			value = (ElemType*)malloc(sizeof(ElemType)*ELEM_SIZE);  //让value能存data
			strcpy_s(value, sizeof(ElemType)*ELEM_SIZE, p->data);  //把data存到value里
			result = add_elem(C, value);
			if (result != 1) {  //插入失败
				printf("求交集操作中出现异常！\n");
				return ERR_MEMORY;
			}
		}
		p = p->next;
	}
	return 1;
}

//16.显示外观
void show_tail() {
	printf("\n");
	printf("********************************************************************************************\n");
	printf("\n");
}