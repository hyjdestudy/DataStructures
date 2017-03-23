#define INCREMENT 10  //每次扩展10个元素的新空间

template <class ElemType>
class SeqQueue {
private:
	ElemType *q_base;  //基地址指针
	int q_front;  //队头指针
	int q_rear;  //队尾指针
	int q_size;  //队大小
public:
	SeqQueue(int size=100);  //1.构造函数
	~SeqQueue();  //2.析构函数
	void clear();  //3.清空队列
	bool is_empty() const;  //4.队列判空
	int get_length() const;  //5.获取队列长度
	ElemType & get_first() const;  //6.取队头元素值
	ElemType & get_last() const;  //7.取队尾元素值
	void append(const ElemType &elem);  //8.入队
	void remove();  //9.出队
	void traverse() const;  //10.遍历队列
	void show_infor() const;  //11.显示队列基本信息
};

//1.构造函数，分配size个结点的顺序空间，构造一个空的循环队列
template <class ElemType>
SeqQueue <ElemType>::SeqQueue(int size) {  
	q_front = q_rear = 0;
	q_base = new ElemType[size];
	q_size = size;
}

//2.析构函数，销毁队列
template <class ElemType>
SeqQueue <ElemType>::~SeqQueue() {
	delete[] q_base;
}

//3.清空队列
template <class ElemType>
void SeqQueue <ElemType>::clear() {
	q_front = q_rear = 0;
}

//4.队列判空
template <class ElemType>
bool SeqQueue <ElemType>::is_empty() const{
	return q_front == q_rear;
}

//5.获取队列长度
template <class ElemType>
int SeqQueue<ElemType>::get_length() const{
	return (q_rear - q_front + q_size) % q_size;
}

//6.取队头元素值，前提是队列非空
template <class ElemType>
ElemType & SeqQueue <ElemType>::get_first() const {
	return q_base[q_front];
}

//7.取队尾元素值，前提是队列非空
template <class ElemType>
ElemType & SeqQueue <ElemType>::get_last() const{
	return q_base[(q_rear - 1 + q_size) % q_size];
}

//8.入队，插入elem到队尾
template <class ElemType>
void SeqQueue <ElemType>::append(const ElemType &elem) {
	//如果队满，扩充空间,一定注意是队列满了以后再扩，此时队头和队尾指针正好是挨着的
	if ((q_rear + 1) % q_size == q_front) {
		ElemType *newbase;
		newbase = new ElemType[q_size+INCREMENT];  //分配新空间
		int i = 0, j = 0;  //i用于遍历原队列，j用于复制到新队列里
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

//9.出队，先决条件是队列非空
template <class ElemType>
void SeqQueue <ElemType>::remove() {
	q_front = (q_front + 1) % q_size;
}

//10.遍历
template <class ElemType>
void SeqQueue <ElemType>::traverse() const {
	if (q_front == q_rear) {
		cout << "队列为空，不能遍历！" << endl;
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

//11.显示队列基本信息
template <class ElemType>
void SeqQueue <ElemType>::show_infor() const {
	cout << "--队列基本信息--" << endl;
	char *msg = (this->is_empty()) ? "是" : "否";
	cout << "队列是否为空："<<msg<<endl;
	cout << "队列总容量：" << this->q_size << endl;
	cout << "队列有效长度：" << this->get_length() << endl;
	if (!(this->is_empty())) {  //队列不空
		cout << "队头元素：" << this->get_first() << endl;
		cout << "队尾元素：" << this->get_last() << endl;
		cout << "遍历队列：" << endl;
		this->traverse();
	}
	else {
		cout << "队头元素：空"  << endl;
		cout << "队尾元素：空"  << endl;
	}
}
