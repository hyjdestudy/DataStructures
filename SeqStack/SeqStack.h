#define INCREMENT 10  //每次扩展10个元素空间

//定义顺序栈
template <class ElemType>
class SeqStack {
private:
	ElemType *s_base;  //基地址指针
	int s_top;  //栈顶指针
	int s_size;  //栈容量

public:
	SeqStack(int size);  //1.构造函数，新建一个容量为size的空栈
	~SeqStack();  //2.析构函数，销毁栈
	void clear();  //3.清空栈
	bool is_empty() const;  //4.判栈空（常成员函数，不能修改成员变量的值，也不能调用类中非const函数）
	int get_length() const;  //5.获取栈中元素的个数
	ElemType &get_top() const;  //6.取栈顶元素（暂时把它理解为返回指针）
	void push(const ElemType &elem);  //7.入栈
	void pop();  //8.出栈	
	void show_infor() const;  //9.显示自身信息
};

//1.初始化顺序栈
template <class ElemType>
SeqStack  <ElemType>::SeqStack(int size) {
	s_base = new ElemType[size];
	s_top = 0;
	s_size = size;
}

//2.销毁顺序栈
template <class ElemType>
SeqStack  <ElemType>::~SeqStack() {
	if (s_base != NULL) {
		delete[] s_base;
	}
}

//3.清空栈
template <class ElemType>
void SeqStack  <ElemType>::clear() {
	s_top = 0;
}

//4.判栈空
template <class ElemType>
bool SeqStack <ElemType>::is_empty() const {
	return s_top == 0;
}

//5.求实际长度
template <class ElemType>
int SeqStack <ElemType>::get_length() const {
	return s_top;
}

//6.取栈顶元素（需保证栈非空）
template <class ElemType>
ElemType & SeqStack <ElemType>::get_top() const {
	return s_base[s_top - 1];
}

//7.入栈
template <class ElemType>
void SeqStack <ElemType>::push(const ElemType &elem) {
	if (s_top >= s_size) {  //若栈满，扩展空间
		ElemType *new_base;
		new_base = new ElemType[s_size + INCREMENT];  //新扩INCREMENT个空间
		int i = 0;
		for (i = 0; i < s_top; i++) {  //把原来空间里的元素挪到新地方
			new_base[i] = s_base[i];
		}
		delete[] s_base;  //释放原来的空间
		s_base = new_base;  //重置基地址
		s_size += INCREMENT;  //修改栈容量
	}

	s_base[s_top] = elem;  //往栈顶添加新元素
	s_top++;  //栈顶指针上移一个位置
}

//8.出栈（需保证栈不空）
template <class ElemType>
void SeqStack <ElemType>::pop() {
	if (s_top > 0)
		s_top--;
}

//9.显示自身信息
template <class ElemType>
void SeqStack <ElemType>::show_infor() const{
	char msg[10];
	if (this->is_empty()) {
		strcpy_s(msg,"是");
	}
	else {
		strcpy_s(msg, "否");
	}
	cout << "--当前栈的基本信息--" << endl;
	cout << "栈总容量：" << s_size<<endl;
	cout << "是否为空：" <<msg<< endl;
	cout << "已用容量：" << s_top << endl;
}