#define INCREMENT 10  //ÿ����չ10��Ԫ�ص��¿ռ�

template <class ElemType>
class SeqQueue {
private:
	ElemType *q_base;  //����ַָ��
	int q_front;  //��ͷָ��
	int q_rear;  //��βָ��
	int q_size;  //�Ӵ�С
public:
	SeqQueue(int size);  //1.���캯��
	~SeqQueue();  //2.��������
	void clear();  //3.��ն���
	bool is_empty() const;  //4.�����п�
	int get_length() const;  //5.��ȡ���г���
	ElemType & get_first() const;  //6.ȡ��ͷԪ��ֵ
	ElemType & get_last() const;  //7.ȡ��βԪ��ֵ
	void append(const ElemType &elem);  //8.���
	void remove();  //9.����
	void traverse() const;  //10.��������
	void show_infor() const;  //11.��ʾ���л�����Ϣ
};

//1.���캯��������size������˳��ռ䣬����һ���յ�ѭ������
template <class ElemType>
SeqQueue <ElemType>::SeqQueue(int size) {  
	q_front = q_rear = 0;
	q_base = new ElemType[size];
	q_size = size;
}

//2.�������������ٶ���
template <class ElemType>
SeqQueue <ElemType>::~SeqQueue() {
	delete[] q_base;
}

//3.��ն���
template <class ElemType>
void SeqQueue <ElemType>::clear() {
	q_front = q_rear = 0;
}

//4.�����п�
template <class ElemType>
bool SeqQueue <ElemType>::is_empty() const{
	return q_front == q_rear;
}

//5.��ȡ���г���
template <class ElemType>
int SeqQueue<ElemType>::get_length() const{
	return (q_rear - q_front + q_size) % q_size;
}

//6.ȡ��ͷԪ��ֵ��ǰ���Ƕ��зǿ�
template <class ElemType>
ElemType & SeqQueue <ElemType>::get_first() const {
	return q_base[q_front];
}

//7.ȡ��βԪ��ֵ��ǰ���Ƕ��зǿ�
template <class ElemType>
ElemType & SeqQueue <ElemType>::get_last() const{
	return q_base[(q_rear - 1 + q_size) % q_size];
}

//8.��ӣ�����elem����β
template <class ElemType>
void SeqQueue <ElemType>::append(const ElemType &elem) {
	//�������������ռ�,һ��ע���Ƕ��������Ժ���������ʱ��ͷ�Ͷ�βָ�������ǰ��ŵ�
	if ((q_rear + 1) % q_size == q_front) {
		ElemType *newbase;
		newbase = new ElemType[q_size+INCREMENT];  //�����¿ռ�
		int i = 0, j = 0;  //i���ڱ���ԭ���У�j���ڸ��Ƶ��¶�����
		for (i = q_front, j = 0; i < q_rear; i = (i + 1) % q_size, j++) {
			newbase[j] = q_base[i];
		}
		delete[] q_base;
		q_base = newbase;
		q_front = 0;
		q_rear = j;
		q_size += INCREMENT;
	}
	q_base[q_rear] = elem;
	q_rear = (q_rear + 1) % q_size;
}

//9.���ӣ��Ⱦ������Ƕ��зǿ�
template <class ElemType>
void SeqQueue <ElemType>::remove() {
	q_front = (q_front + 1) % q_size;
}

//10.����
template <class ElemType>
void SeqQueue <ElemType>::traverse() const {
	if (q_front == q_rear) {
		cout << "����Ϊ�գ����ܱ�����" << endl;
	}
	else {
		int i = q_front;
		while (i != q_rear) {
			cout << q_base[i] << " ";
			i = (i + 1) % q_size;
		}
		cout << endl;
	}
}

//11.��ʾ���л�����Ϣ
template <class ElemType>
void SeqQueue <ElemType>::show_infor() const {
	cout << "--���л�����Ϣ--" << endl;
	char *msg = (this->is_empty()) ? "��" : "��";
	cout << "�����Ƿ�Ϊ�գ�"<<msg<<endl;
	cout << "������������" << this->q_size << endl;
	cout << "������Ч���ȣ�" << this->get_length() << endl;
	if (!(this->is_empty())) {  //���в���
		cout << "��ͷԪ�أ�" << this->get_first() << endl;
		cout << "��βԪ�أ�" << this->get_last() << endl;
		cout << "�������У�" << endl;
		this->traverse();
	}
	else {
		cout << "��ͷԪ�أ���"  << endl;
		cout << "��βԪ�أ���"  << endl;
	}
}