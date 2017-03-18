//��ջ�Ķ���

template <class ElemType>
struct  LinkNode {  //��ջ���
	ElemType data;
	LinkNode<ElemType> *next;
};

template <class ElemType>
class LinkStack {
private:
	LinkNode<ElemType> *top;  //ջ����������ͷ��
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

//1.��ʼ����ջ
template <class ElemType>
LinkStack <ElemType>::LinkStack() {
	top = NULL;  //��ʼ����ջ��ʱ����ջ��ָ��Ϊ��
}

//2.������ջ
template <class ElemType>
LinkStack <ElemType>::~LinkStack() {
	clear();  //������ջ���ǰ�����ջ����ͷ�
}

//3.�����ջ
template <class ElemType>
void LinkStack <ElemType>::clear() {
	LinkNode<ElemType> *p;
	while (top) {  //ֻҪջ���գ������ͷ������е����н��
		p = top;
		top = top->next;
		delete[] p;
	}
}

//4.��ջ��
template <class ElemType>
bool LinkStack <ElemType>::is_empty() const {
	return top == NULL;
}

//5.�󳤶�
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

//6.ȡջ��Ԫ�ص�ֵ��ǰ����ջ���գ�
template <class ElemType>
ElemType & LinkStack <ElemType>::get_top() const {
	return top->data;
}

//7.��ջ
template <class ElemType>
void LinkStack <ElemType>::push(const ElemType &elem) {
	LinkNode<ElemType> *p;
	p = new LinkNode <ElemType>;
	p->data = elem;
	p->next = top;
	top = p;
}

//8.��ջ��ǰ����ջ���գ�
template <class ElemType>
void LinkStack <ElemType>::pop() {
	LinkNode <ElemType> *p = top;
	top = top->next;
	delete p;
}

//9.��ʾ������Ϣ
template <class ElemType>
void LinkStack <ElemType>::show_infor() {
	char msg[10];
	strcpy_s(msg, (*this).is_empty() ? "��" : "��");
	cout << "--��ǰ��ջ��Ϣ--" << endl;
	cout << "��ǰջ��С��" << (*this).get_length() << endl;
	cout << "�Ƿ�Ϊ�գ�" << msg << endl;
	if (!(*this).is_empty()) {
		cout << "ջ��Ԫ�أ�" << this->get_top() << endl;
	}
	cout << endl;
}
