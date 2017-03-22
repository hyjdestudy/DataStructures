//��ͷ���������ж���
template <class ElemType>
struct LinkNode {
	ElemType data;
	LinkNode *next;
};

template <class ElemType>
class LinkQueue {
private:
	LinkNode<ElemType> *q_front;  //��ͷָ��
	LinkNode<ElemType> *q_rear;  //��βָ��
public:
	LinkQueue();  //1.���캯��
	~LinkQueue();  //2.��������
	void clear();  //3.���������
	bool is_empty() const;  //4.�п�
	int get_length() const;  //5.��ö��г���
	ElemType & get_first() const;  //6.��ö�ͷԪ��
	ElemType & get_last() const;  //7.��ö�βԪ��
	void append(const ElemType &elem);  //8.���
	void remove();  //9.����
	void traverse() const;  //10.��������
	void show_infor() const;  //11.��ʾ���л�����Ϣ
};

//1.���캯������ʼ��һ��ֻ��ͷ����������
template <class ElemType>
LinkQueue<ElemType>::LinkQueue() {
	q_front = q_rear = new LinkNode<ElemType>;  //����ͷ���
	q_front->next = NULL;
}

//2.�����������ͷ����н��
template <class ElemType>
LinkQueue<ElemType>::~LinkQueue() {
	
}

//3.���������
template <class ElemType>
void LinkQueue<ElemType>::clear() {
	LinkNode<ElemType> *p;
	while (q_front->next != NULL) {  //�嵽ֻʣ���һ�����
		p = q_front;
		q_front = p->next;
		delete p;
	}
	q_rear = q_front;
}

//4.�����п�
template <class ElemType>
bool LinkQueue<ElemType>::is_empty() const {
	return q_front == q_rear;
}

//5.����г���
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

//6.��ö�ͷԪ�أ��Ⱦ������Ƕ��в���
template <class ElemType>
ElemType & LinkQueue<ElemType>::get_first() const {
	return q_front->next->data;
}

//7.ȡ��βԪ�أ��Ⱦ������Ƕ��в���
template <class ElemType>
ElemType & LinkQueue<ElemType>::get_last() const {
	return q_rear->data;
}

//8.���
template <class ElemType>
void LinkQueue<ElemType>::append(const ElemType &elem) {
	//�½�һ�����
	LinkNode<ElemType> *p = new LinkNode<ElemType>;
	p->data = elem;
	p->next = NULL;
	q_rear->next = p;
	//�Ѷ�βָ��ָ�����һ��Ԫ��
	q_rear = p;
}

//9.���ӣ��Ⱦ������Ƕ��в���
template <class ElemType>
void LinkQueue<ElemType>::remove() {
	LinkNode<ElemType> *p = q_front->next;
	q_front->next = p->next;
	if (p == q_rear) {  //������ӵ�ǡ�������һ����㣬��Ҫ�޸Ķ�βָ��
		q_rear = q_front;
	}
	delete p;
}

//10.��������
template <class ElemType>
void LinkQueue<ElemType>::traverse() const {
	if (q_front == q_rear) {
		cout << "�ն��У����ܱ�����" << endl;
		return;
	}
	LinkNode<ElemType> *p = q_front->next;
	while (p) {
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}

//11.��ʾ���л�����Ϣ
template <class ElemType>
void LinkQueue<ElemType>::show_infor() const {
	cout << "--���л�����Ϣ--" << endl;
	char *msg=this->is_empty() ? "��" : "��";
	cout << "�����Ƿ�Ϊ�գ�" << msg << endl;
	cout << "���г��ȣ�" << this->get_length() << endl;
	if (!(this->is_empty())) {  //���в���
		cout << "��ͷԪ�أ�" << this->get_first() << endl;
		cout << "��βԪ�أ�" << this->get_last() << endl;
		cout << "�������У�" << endl;
		this->traverse();
	}
	else {
		cout << "��ͷԪ�أ���" << endl;
		cout << "��βԪ�أ���" << endl;
	}
}