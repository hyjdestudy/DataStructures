#define INCREMENT 10  //ÿ����չ10���ַ��Ŀռ�

class MyString {
private:
	char *ch;  //ָ��̬����洢���׵�ַ���ַ�ָ��
	int length;  //����ʵ�ʳ���
	int size;  //��������
public:
	MyString(int s=10);  //1.���캯��
	~MyString();  //2.��������
	int get_length() const;  //3.ȡ����
	void assign_str(const char *str);  //4.���ַ�����ֵ
	int compare(const MyString &str);  //5.���Ƚ�
	void connect(const MyString &str);  //6.������
	char *get_substring(int start,int end);  //7.ȡ�Ӵ�
	void clear();  //8.��մ�
	void show() const;  //9.��ʾ������
	void show_infor() const;  //10.��ʾ���Ļ�����Ϣ
};

//1.���캯��
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

//2.��������
MyString::~MyString() {
	/*
	cout << ch << "����������" << endl;
	system("pause");
	*/
	delete[] ch;
}

//3.ȡ����
int MyString::get_length() const {
	return length;
}

//4.�����ַ����������ڴ������룩
void MyString::assign_str(const char *str) {
	if (!str) {
		cout << "���ܶԿմ�ִ�и��Ʋ�����" << endl;
		return;
	}
	int i = 0;
	int j = 0;
	do {
		if (i >= size-1) {  
			/*Ҫ���ʵ�size-1���ˣ������ַ��������һ��λ�ã���'\0'�ġ�
			˵����ǰ�ַ���Ҫ�����ˣ�Ҫ���ݣ�Ĭ���±�Ϊsize-1�ĵط���'\0'��0~size-1ǡΪsize���ط���*/
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
	} while (str[i] != '\0');  //�´θ����'\0'��
	ch[i] = '\0';
	length = i;  //����ǡΪ'\0'����λ�õ��±꣨�磺�ַ���abcd,'\0'���±�Ϊ4�ĵط�������Ϊ4��
}

//5.���Ƚϣ�ǰ���Ǵ��ǿգ�
int MyString::compare(const MyString &str) {
	int i = 0;
	//while (i<length && i<str.get_length()) {
	while (ch[i]!='\0' && str.ch[i]!='\0') {
		if (ch[i]!=str.ch[i]) {
			return ch[i] - str.ch[i];
		}
		i++;
	}
	//û�ȳ��������Ƚ����Ĵ��Ƕ̴���ΪС�����磺app��apple��app��apple֮ǰ
	return length - str.get_length();
}

//6.������
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
	length = i;  //�޸Ĵ���
}

//7.ȡ�Ӵ�
char* MyString::get_substring(int start, int end) {  //��ȡ��start��end���Ӵ�������start��end
	if (start<0 || start>length-1|| end<0 || end>length-1 || start > end) {
		cout << "�Ƿ���ʼλ�ã�" << endl;
		return NULL;
	}
	int len = end - start + 1;  
	char *sub = new char[len+1];  //���һ��λ�÷�'\0'
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

//8.��մ�
void MyString::clear() {
	if (ch != NULL)
		delete[] ch;
	ch = NULL;
	length = 0;
}

//9.��ʾ������
void MyString::show() const {
	if (!ch) {
		cout << "��" ;
	}
	else {
		cout << ch ;
	}
}

//10.��ʾ���Ļ�����Ϣ
void MyString::show_infor() const {
	cout << "--�ַ���������Ϣ--" << endl;
	cout << "�ַ������ݣ�";
	show();
	cout << endl;
	cout << "�ַ������ȣ�" << length << endl;
	cout << "�ַ���������" << size << endl;
}

