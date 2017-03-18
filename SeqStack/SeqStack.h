#define INCREMENT 10  //ÿ����չ10��Ԫ�ؿռ�

//����˳��ջ
template <class ElemType>
class SeqStack {
private:
	ElemType *s_base;  //����ַָ��
	int s_top;  //ջ��ָ��
	int s_size;  //ջ����

public:
	SeqStack(int size);  //1.���캯�����½�һ������Ϊsize�Ŀ�ջ
	~SeqStack();  //2.��������������ջ
	void clear();  //3.���ջ
	bool is_empty() const;  //4.��ջ�գ�����Ա�����������޸ĳ�Ա������ֵ��Ҳ���ܵ������з�const������
	int get_length() const;  //5.��ȡջ��Ԫ�صĸ���
	ElemType &get_top() const;  //6.ȡջ��Ԫ�أ���ʱ�������Ϊ����ָ�룩
	void push(const ElemType &elem);  //7.��ջ
	void pop();  //8.��ջ	
	void show_infor() const;  //9.��ʾ������Ϣ
};

//1.��ʼ��˳��ջ
template <class ElemType>
SeqStack  <ElemType>::SeqStack(int size) {
	s_base = new ElemType[size];
	s_top = 0;
	s_size = size;
}

//2.����˳��ջ
template <class ElemType>
SeqStack  <ElemType>::~SeqStack() {
	if (s_base != NULL) {
		delete[] s_base;
	}
}

//3.���ջ
template <class ElemType>
void SeqStack  <ElemType>::clear() {
	s_top = 0;
}

//4.��ջ��
template <class ElemType>
bool SeqStack <ElemType>::is_empty() const {
	return s_top == 0;
}

//5.��ʵ�ʳ���
template <class ElemType>
int SeqStack <ElemType>::get_length() const {
	return s_top;
}

//6.ȡջ��Ԫ�أ��豣֤ջ�ǿգ�
template <class ElemType>
ElemType & SeqStack <ElemType>::get_top() const {
	return s_base[s_top - 1];
}

//7.��ջ
template <class ElemType>
void SeqStack <ElemType>::push(const ElemType &elem) {
	if (s_top >= s_size) {  //��ջ������չ�ռ�
		ElemType *new_base;
		new_base = new ElemType[s_size + INCREMENT];  //����INCREMENT���ռ�
		int i = 0;
		for (i = 0; i < s_top; i++) {  //��ԭ���ռ����Ԫ��Ų���µط�
			new_base[i] = s_base[i];
		}
		delete[] s_base;  //�ͷ�ԭ���Ŀռ�
		s_base = new_base;  //���û���ַ
		s_size += INCREMENT;  //�޸�ջ����
	}

	s_base[s_top] = elem;  //��ջ�������Ԫ��
	s_top++;  //ջ��ָ������һ��λ��
}

//8.��ջ���豣֤ջ���գ�
template <class ElemType>
void SeqStack <ElemType>::pop() {
	if (s_top > 0)
		s_top--;
}

//9.��ʾ������Ϣ
template <class ElemType>
void SeqStack <ElemType>::show_infor() const{
	char msg[10];
	if (this->is_empty()) {
		strcpy_s(msg,"��");
	}
	else {
		strcpy_s(msg, "��");
	}
	cout << "--��ǰջ�Ļ�����Ϣ--" << endl;
	cout << "ջ��������" << s_size<<endl;
	cout << "�Ƿ�Ϊ�գ�" <<msg<< endl;
	cout << "����������" << s_top << endl;
}