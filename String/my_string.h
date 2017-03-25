#define INCREMENT 10  //每次扩展10个字符的空间

class MyString {
private:
	char *ch;  //指向动态分配存储区首地址的字符指针
	int length;  //串的实际长度
	int size;  //串的容量
public:
	MyString(int s=10);  //1.构造函数
	~MyString();  //2.析构函数
	int get_length() const;  //3.取串长
	void assign_str(const char *str);  //4.给字符串赋值
	int compare(const MyString &str);  //5.串比较
	void connect(const MyString &str);  //6.串连接
	char *get_substring(int start,int end);  //7.取子串
	void clear();  //8.清空串
	void show() const;  //9.显示串内容
	void show_infor() const;  //10.显示串的基本信息
};

//1.构造函数
MyString::MyString(int s) {
	if (s == 0) {
		ch = NULL;
	}
	else {
		ch = new char[s];
	}	
	length = 0;
	size = s;
}

//2.析构函数
MyString::~MyString() {
	/*
	cout << ch << "的析构函数" << endl;
	system("pause");
	*/
	delete[] ch;
}

//3.取串长
int MyString::get_length() const {
	return length;
}

//4.复制字符串（可用于串的输入）
void MyString::assign_str(const char *str) {
	if (!str) {
		cout << "不能对空串执行复制操作！" << endl;
		return;
	}
	int i = 0;
	int j = 0;
	do {
		if (i >= size-1) {  
			/*要访问到size-1处了，这是字符串的最后一个位置，放'\0'的。
			说明当前字符串要存满了，要扩容（默认下标为size-1的地方存'\0'，0~size-1恰为size个地方）*/
			char *new_ch = new char[size + INCREMENT];
			size += INCREMENT;
			j = 0;
			for (j = 0; j < i; j++) {
				new_ch[j] = ch[j];
			}
			delete[] ch;
			ch = new_ch;
		}
		ch[i] = str[i];
		i++;
	} while (str[i] != '\0');  //下次该填充'\0'了
	ch[i] = '\0';
	length = i;  //长度恰为'\0'所在位置的下标（如：字符串abcd,'\0'在下标为4的地方，长度为4）
}

//5.串比较（前提是串非空）
int MyString::compare(const MyString &str) {
	int i = 0;
	//while (i<length && i<str.get_length()) {
	while (ch[i]!='\0' && str.ch[i]!='\0') {
		if (ch[i]!=str.ch[i]) {
			return ch[i] - str.ch[i];
		}
		i++;
	}
	//没比出来，则先结束的串是短串，为小串。如：app和apple，app在apple之前
	return length - str.get_length();
}

//6.串连接
void MyString::connect(const MyString &str) {
	int i = 0;
	i = length;
	int j = 0;
	do {
		if (i >= size - 1) {
			char *new_ch = new char[size + INCREMENT];
			size += INCREMENT;
			int k = 0;
			for (k = 0; k < i; k++) {
				new_ch[k] = ch[k];
			}
			delete[] ch;
			ch = new_ch;
		}
		ch[i] = str.ch[j];
		i++;
		j++;
	} while (str.ch[j] != '\0');
	ch[i] = '\0';
	length = i;  //修改串长
}

//7.取子串
char* MyString::get_substring(int start, int end) {  //截取从start到end的子串，包含start和end
	if (start<0 || start>length-1|| end<0 || end>length-1 || start > end) {
		cout << "非法起始位置！" << endl;
		return NULL;
	}
	int len = end - start + 1;  
	char *sub = new char[len+1];  //最后一个位置放'\0'
	int i = start;
	int j = 0;
	while (i <= end) {
		sub[j] = ch[i];
		i++;
		j++;
	}
	sub[j] = '\0';
	return sub;
}

//8.清空串
void MyString::clear() {
	if (ch != NULL)
		delete[] ch;
	ch = NULL;
	length = 0;
}

//9.显示串内容
void MyString::show() const {
	if (!ch) {
		cout << "空" ;
	}
	else {
		cout << ch ;
	}
}

//10.显示串的基本信息
void MyString::show_infor() const {
	cout << "--字符串基本信息--" << endl;
	cout << "字符串内容：";
	show();
	cout << endl;
	cout << "字符串长度：" << length << endl;
	cout << "字符串容量：" << size << endl;
}

