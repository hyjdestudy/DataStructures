//链栈的定义

template <class ElemType>
struct  LinkNode {  //链栈结点
	ElemType data;
	LinkNode<ElemType> *next;
};

template <class ElemType>
class LinkStack {
private:
	LinkNode<ElemType> *top;  //栈操作都是在头部
public:
	LinkStack();
	~LinkStack();
	void clear();
	bool is_empty() const;
	int get_length() const;
	ElemType & get_top() const;
	void push(const ElemType &elem);
	void pop();
	void show_infor();
};

//1.初始化链栈
template <class ElemType>
LinkStack <ElemType>::LinkStack() {
	top = NULL;  //初始化链栈的时候，让栈顶指针为空
}

//2.销毁链栈
template <class ElemType>
LinkStack <ElemType>::~LinkStack() {
	clear();  //销毁链栈就是把所有栈结点释放
}

//3.清空链栈
template <class ElemType>
void LinkStack <ElemType>::clear() {
	LinkNode<ElemType> *p;
	while (top) {  //只要栈不空，依次释放链表中的所有结点
		p = top;
		top = top->next;
		delete[] p;
	}
}

//4.判栈空
template <class ElemType>
bool LinkStack <ElemType>::is_empty() const {
	return top == NULL;
}

//5.求长度
template <class ElemType>
int LinkStack <ElemType>::get_length() const {
	int i = 0;
	LinkNode<ElemType> *p = top;
	while (p) {
		i++;
		p = p->next;
	}
	return i;
}

//6.取栈顶元素的值（前提是栈不空）
template <class ElemType>
ElemType & LinkStack <ElemType>::get_top() const {
	return top->data;
}

//7.入栈
template <class ElemType>
void LinkStack <ElemType>::push(const ElemType &elem) {
	LinkNode<ElemType> *p;
	p = new LinkNode <ElemType>;
	p->data = elem;
	p->next = top;
	top = p;
}

//8.出栈（前提是栈不空）
template <class ElemType>
void LinkStack <ElemType>::pop() {
	LinkNode <ElemType> *p = top;
	top = top->next;
	delete p;
}

//9.显示自身信息
template <class ElemType>
void LinkStack <ElemType>::show_infor() {
	char msg[10];
	strcpy_s(msg, (*this).is_empty() ? "是" : "否");
	cout << "--当前链栈信息--" << endl;
	cout << "当前栈大小：" << (*this).get_length() << endl;
	cout << "是否为空：" << msg << endl;
	if (!(*this).is_empty()) {
		cout << "栈顶元素：" << this->get_top() << endl;
	}
	cout << endl;
}
