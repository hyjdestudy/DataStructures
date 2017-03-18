/*
description:单循环链表实现约瑟夫环问题
author:胡宇杰
date:2017-03-17
*/

#include <stdio.h>
#include <stdlib.h>

#define ERR_INVALIDPARAM -1  //非法参数
#define ERR_MEMORY  -2//内存错误

typedef struct Pirate {
	int id;  //海盗的编号
	struct Pirate *next;
}Pirate,Group;  //结点用Pirate，循环链表用Group

/*函数声明*/
int init_group(Group *G,int n);  //1.建立包含n个元素的约瑟夫环（带头结点）
void josephus_op(Group *G,int n);  //2.约瑟夫环算法（带头结点）
Group* init_group_without_head(Group *G, int n);  //3.建立n个元素的约瑟夫环（不带头结点）
void josephus_op_without_head(Group *G, int num);  //4.约瑟夫环算法（不带头结点）
void show_tail();  //5.显示外观

int main() {
	int choice = 1;  //接收用户选择的菜单
	char ch = ' ';  //吸收回车符
	int pirates=0;  //指定有多少海盗
	int number = 0;  //指定死亡数字
	Group *G = NULL;  //海盗群
	Group *New_G = NULL;
	int status = 0;  //接收操作的执行状态
	bool is_active = true;  //游戏是否正在进行

	printf("\t\t\t\t\t----约瑟夫环海盗求生游戏----\n\n");
	printf("故事描述：\n");
	printf("n个海盗在荒岛上，只有1杯水，他们决定站成一圈从1开始报数，谁报到死亡数字num就自杀,"
		"之后下一位重新从1开始报，直到只剩下最后一个人，这杯水归他。\n");	
	printf("\n");

	while (is_active) {
		//建立约瑟夫环
		G = (Group*)malloc(sizeof(Pirate));
		if (!G) {
			printf("内存分配异常，不能运行程序！\n");
			system("pause");
			return 0;
		}
		printf("\t\t\t\t\t\t--游戏菜单--\n");
		printf("\n1.使用含头结点的单循环链表\t\t2.使用无头结点的单循环链表\t\t3.退出游戏\n");
		printf("请选择：");
		scanf_s("%d", &choice);
		ch = getchar();

		if (choice == 1 || choice == 2) {
			do {
				printf("请输入海盗数：");
				scanf_s("%d", &pirates);
				ch = getchar();  //吸收回车符
				printf("请指定死亡数字：");
				scanf_s("%d", &number);
				ch = getchar();
			} while (pirates<0 || number<0);
		}				
		
		switch (choice)
		{
		case 1:
			printf("\t\t\t\t\t--使用含头结点的单循环链表--\n");
			//建立海盗群
			status = init_group(G, pirates);
			if (status < 0) {
				printf("建立海盗群失败，不能运行程序！\n");
				system("pause");
				return 0;
			}
			//海盗报数
			josephus_op(G, number);
			show_tail();
			break;
		case 2:
			printf("\t\t\t\t\t--使用无头结点的单循环链表--\n");
			//建立海盗群
			New_G = init_group_without_head(G, pirates);
			if (!New_G) {
				printf("建立海盗群失败，不能运行程序！\n");
				system("pause");
				return 0;
			}
			//海盗报数
			josephus_op_without_head(New_G, number);
			show_tail();
			break;
		case 3:
			printf("\t\t\t\t\t\t--退出游戏--\n");
			is_active = false;
			printf("您已成功退出游戏！\n");
			show_tail();
			break;
		default:
			printf("\t\t\t\t\t\t--选择错误--\n");
			printf("菜单输入错误，请重新选择！\n");
			show_tail();
		}
	}

	system("pause");
	return 0;
}

/*函数实现*/
//1.建立n个元素的约瑟夫环（带头结点）
int init_group(Group *G,int n) {
	if (!G) {
		printf("无效地址，不能建立约瑟夫环！\n");
		return ERR_INVALIDPARAM;
	}
	G->next = G;  //初始化头结点，此时表示单循环链表为空
	Pirate *r = G;  //r指针时刻指向单循环链表的最后一个位置
	Pirate *p;  //用于做新结点
	if (n < 0) {
		printf("海盗人数必须大于0！\n");
		return ERR_INVALIDPARAM;
	}
	int i = 0;
	for (i = 1; i <= n; i++) {
		p = (Pirate*)malloc(sizeof(Pirate));
		if (!p) {
			printf("建立新结点异常！\n");
			return ERR_MEMORY;
		}
		p->id = i;
		//把新结点p挂到链表最后一个位置
		p->next = r->next;
		r->next = p;
		//r指向最后一个结点
		r = r->next;
	}
	return 1;
}

//2.约瑟夫环算法（带头结点）
void josephus_op(Group *G, int num) {
	if (!G) {
		printf("无效地址，不能执行约瑟夫环算法！\n");
		system("pause");
		return;
	}
	int count = 1;  //输出出队的顺序
	int i = 1;  //报数用
	Pirate *pre = G;  //指向当前结点p的前驱
	Pirate *p = G->next;
	Pirate *q;  //用于释放内存

	while (p->next != pre) {  //当只剩下一个人的时候，停止（注意：p最后可能指向头结点，也可能指向最后一个活着的海盗）
		if (p != G) {  //不是头结点就都得报数
			printf("%d号海盗报数：%d\n", p->id, i);
			if (i == num) {  //这个人报的数是num，要自杀
				printf("第%d个自杀的海盗是%d号！\n", count++, p->id);
				q = p;  //暂存要删除的结点
				pre->next = p->next;  
				p = p->next;  //因为杀了一个，所以前驱不变，只让p往后挪一个
				free(q);
				i = 1;  //重新报数
			}
			else {  //没有报到死亡数字，继续往后报
				i++;
				pre = p;
				p = p->next;
			}			
		}
		else {  //头结点不用报数
			pre = p;
			p = p->next;
		}
	}
	printf("\n");
	if (p == G) {  //如果p最后指向的是头结点G，而不是海盗
		p = p->next;  
	}
	printf("最后活下来的海盗是%d号\n",p->id);
}

//3.建立n个元素的约瑟夫环（不带头结点）
Pirate* init_group_without_head(Group *G, int n) {
	//调用带头结点的初始化方法
	int status=init_group(G,n);
	if (status < 0) {
		printf("初始化单链表失败，不能建立约瑟夫环！\n");
		return NULL;
	}
	Pirate *r = G->next;  //用r去找最后一个结点
	while (r->next != G) {
		r = r->next;
	}
	
	//去掉头结点
	r->next = G->next;  //把最后一个结点的next指针指向第一个结点
	Pirate *New_G = G->next;
	free(G);
	return New_G;
}

//4.约瑟夫环算法（不带头结点）
void josephus_op_without_head(Group *G, int num) {
	if (!G) {
		printf("无效地址，不能执行约瑟夫环算法！\n");
		system("pause");
		return;
	}
	int count = 1;  //输出出队的顺序
	int i = 1;  //报数用
	Pirate *pre = G;  //用pre去找最后一个结点，即第一个结点的前驱
	while (pre->next != G) {
		pre = pre->next;
	}
	Pirate *p = G;  //p用于指向当前结点
	Pirate *q;  //用于释放内存

	while (p->next != p) {  //当只剩下一个人的时候，停止
		printf("%d号海盗报数：%d\n", p->id, i);
		if (i == num) {  //这个人报的数是num，要自杀
			printf("第%d个自杀的海盗是%d号！\n", count++, p->id);
			q = p;  //暂存要删除的结点
			pre->next = p->next;
			p = p->next;  //因为杀了一个，所以前驱不变，只让p往后挪一个
			free(q);
			i = 1;  //重新报数
		}
		else {  //没有报到死亡数字，继续往后报
			i++;
			pre = p;
			p = p->next;
		}
	}
	printf("\n");
	printf("最后活下来的海盗是%d号\n", p->id);
}

//5.显示外观
void show_tail() {
	printf("\n");
	int i = 0;
	while (i != 110) {
		printf("*");
		i++;
	}
	printf("\n\n");
}