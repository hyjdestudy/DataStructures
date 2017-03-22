//带头结点的链队列定义
template <class ElemType>
struct LinkNode {
	ElemType data;
	LinkNode *next;
};

template <class ElemType>
class LinkQueue {
private:
	LinkNode<ElemType> *q_front;  //队头指针
	LinkNode<ElemType> *q_rear;  //队尾指针
public:
	LinkQueue();  //1.构造函数
	~LinkQueue();  //2.析构函数
	void clear();  //3.清空链队列
	bool is_empty() const;  //4.判空
	int get_length() const;  //5.获得队列长度
	ElemType & get_first() const;  //6.获得队头元素
	ElemType & get_last() const;  //7.获得队尾元素
	void append(const ElemType &elem);  //8.入队
	void remove();  //9.出队
	void traverse() const;  //10.遍历队列
	void show_infor() const;  //11.显示队列基本信息
};

//1.构造函数，初始化一个只有头结点的链队列
template <class ElemType>
LinkQueue<ElemType>::LinkQueue() {
	q_front = q_rear = new LinkNode<ElemType>;  //分配头结点
	q_front->next = NULL;
}

//2.析构函数，释放所有结点
template <class ElemType>
LinkQueue<ElemType>::~LinkQueue() {
	
}

//3.清空链队列
template <class ElemType>
void LinkQueue<ElemType>::clear() {
	LinkNode<ElemType> *p;
	while (q_front->next != NULL) {  //清到只剩最后一个结点
		p = q_front;
		q_front = p->next;
		delete p;
	}
	q_rear = q_front;
}

//4.队列判空
template <class ElemType>
bool LinkQueue<ElemType>::is_empty() const {
	return q_front == q_rear;
}

//5.求队列长度
template <class ElemType>
int LinkQueue<ElemType>::get_length() const {
	int i = 0;
	LinkNode<ElemType> *p = q_front->next;
	while (p != NULL) {
		i++;
		p = p->next;
	}
	return i;
}

//6.获得队头元素，先决条件是队列不空
template <class ElemType>
ElemType & LinkQueue<ElemType>::get_first() const {
	return q_front->next->data;
}

//7.取队尾元素，先决条件是队列不空
template <class ElemType>
ElemType & LinkQueue<ElemType>::get_last() const {
	return q_rear->data;
}

//8.入队
template <class ElemType>
void LinkQueue<ElemType>::append(const ElemType &elem) {
	//新建一个结点
	LinkNode<ElemType> *p = new LinkNode<ElemType>;
	p->data = elem;
	p->next = NULL;
	q_rear->next = p;
	//把队尾指针指向最后一个元素
	q_rear = p;
}

//9.出队，先决条件是队列不空
template <class ElemType>
void LinkQueue<ElemType>::remove() {
	LinkNode<ElemType> *p = q_front->next;
	q_front->next = p->next;
	if (p == q_rear) {  //如果出队的恰好是最后一个结点，则要修改队尾指针
		q_rear = q_front;
	}
	delete p;
}

//10.遍历队列
template <class ElemType>
void LinkQueue<ElemType>::traverse() const {
	if (q_front == q_rear) {
		cout << "空队列，不能遍历！" << endl;
		return;
	}
	LinkNode<ElemType> *p = q_front->next;
	while (p) {
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}

//11.显示队列基本信息
template <class ElemType>
void LinkQueue<ElemType>::show_infor() const {
	cout << "--队列基本信息--" << endl;
	char *msg=this->is_empty() ? "是" : "否";
	cout << "队列是否为空：" << msg << endl;
	cout << "队列长度：" << this->get_length() << endl;
	if (!(this->is_empty())) {  //队列不空
		cout << "队头元素：" << this->get_first() << endl;
		cout << "队尾元素：" << this->get_last() << endl;
		cout << "遍历队列：" << endl;
		this->traverse();
	}
	else {
		cout << "队头元素：空" << endl;
		cout << "队尾元素：空" << endl;
	}
}