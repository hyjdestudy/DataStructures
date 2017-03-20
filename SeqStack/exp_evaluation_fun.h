using namespace std;  //����cout, endl����

//������ʽ�ľ��庯��
char ops[7] = { '+', '-', '*', '/', '(', ')', '=' };
//
/*
��������ȼ��ıȽϾ���op1�������ջջ��Ԫ�أ�op2�����ڶ���������
N��ʾ����ȷ�ı��ʽ�в�����ִ������
----------
op1\op2|   +   -   *    \   (   )   =
----------
+                >   >   <  <  <  >  >
-                 >   >   <  <  <  >  >
*                >   >   >   >  < >  >
/                 >   >   >   >  < >  >
(                 <   <   <   <  < =  N
)                 >   >   >   >  N >  >
=                <   <   <   <  < N  =
*/
char cmp[7][7] = {
	{ '>', '>', '<', '<', '<', '>', '>' },
	{ '>', '>', '<', '<', '<', '>', '>' },
	{ '>', '>', '>', '>', '<', '>', '>' },
	{ '>', '>', '>', '>', '<', '>', '>' },
	{ '<', '<', '<', '<', '<', '=', ' ' },
	{ '>', '>', '>', '>', ' ', '>', '>' },
	{ '<', '<', '<', '<', '<', ' ', ' ' },
};

//1.�ж��ַ�ch�Ƿ�Ϊ�����
bool is_operator(char ch);
//2.�Ƚ������ch1��ch2�����ȼ�
char compare(char ch1, char ch2);
//3.������ʽ z = x <op> y ��ע�������Ϊ0
bool compute(double x, char op, double y, double &z);
//4.������ʽ��ֵ
bool compute_exp(char *str, double &result);

//1.�ж��ַ�ch�Ƿ�Ϊ�����
bool is_operator(char ch) {
	int i = 0;
	for (i = 0; i < 7; i++) {
		if (ch == ops[i])
			return true;
	}
	return false;
}

//2.�Ƚ������ch1��ch2�����ȼ���ch1��ջ����ch2�����ڶ�����������
char compare(char ch1, char ch2) {
	int i, p1, p2;  //m,n����ȷ��ch1��ch2�ھ����е�λ��
	char priority = ' ';
	for (i = 0; i < 7; i++) {
		if (ops[i] == ch1) {
			p1 = i;
		}
		if (ops[i] == ch2) {
			p2 = i;
		}
	}
	priority = cmp[p1][p2];
	return priority;
}

//3.������ʽ z = x <op> y ��ע�������Ϊ0
bool compute(double x, char op, double y, double &z) {
	switch (op) {
	case '+':
		z = x + y;
		break;
	case '-':
		z = x - y;
		break;
	case '*':
		z = x*y;
		break;
	case '/':
		if (y != 0.0) {
			z = x / y;
			break;
		}
		else {
			cout << "����Ϊ0������" << endl;
			return false;
		}
	}
	return true;
}

//4.������ʽ��ֵ
bool compute_exp(char *str, double &exp_result) {
	char ch = ' ';  //��Ŷ�����ַ�
	int temp = 0;  //���ַ�ת��������
	char op = ' ';  //���ڴ�ŴӲ�����ջ�������������������������
	double n1 = 0, n2 = 0, n3 = 0;  //�Ӳ�����ջ��������������n1��n2��������n1 <op> n2�浽n3��
	char priority = ' ';  //�����ж�ջ��������͵�ǰ��������������ȼ�
	int i = 0;  //���ڱ������ʽ
	SeqStack <char> op_stack(20);  //�����ջ
	SeqStack <double> num_stack(20);  //������ջ

									  //�ѡ�=��ѹ��ջ
	op_stack.push('=');
	//������ʽ
	ch = str[i++];
	while (ch != '=' || op_stack.get_top() != '=') {  //��һ���ֱ�֤�ѱ��ʽ���꣬�ڶ����ֱ�֤�������ջ���op������
		while (ch == ' ') {  //���˿ո�
			ch = str[i++];
		}
		if (is_operator(ch)) {  //�������
			priority = compare(op_stack.get_top(), ch);  //�ж�ջ��������͵�ǰ����������ȼ�
			switch (priority) {
			case '<':  //��ǰ��������ȼ��ߣ�ֱ����ջ
				op_stack.push(ch);
				ch = str[i++];
				break;

			case '>':  //��ǰ��������ȼ��ͣ�Ҫ�ȵ���ջ��������������㣬�㵽��ǰ�������
				op = op_stack.get_top();  //���������ջ�������
				op_stack.pop();
				n2 = num_stack.get_top();  //�ȵ����Ĳ������ǵ�2��������
				num_stack.pop();
				n1 = num_stack.get_top();  //�󵯳��Ĳ������ǵ�1��������
				num_stack.pop();
				if (compute(n1, op, n2, n3)) {  //����n3 = n1 <op> n2 
					num_stack.push(n3);  //�µļ�����ѹ��ջ��
					break;
				}
				else {  //��������˳�����
					exp_result = 0;
					return false;
				}

			case '=':
				/*ֻ�е�ǰ����Ϊ��������ջ������Ϊ������ʱ������ִ��������
				��ǰ��������������ı��ʽ�����ڱ��ʽ�����ˣ����Ҳ�������ջ���ˣ���ʣ��������*/
				op_stack.pop();  //������
				ch = str[i++];  //������һ���ַ�
				break;
			}
		}
		else {  //��ǰ�������������
			temp = ch - '0';  //�ѵ�ǰ������ַ�ת������
			ch = str[i++];  //���������
			while (!is_operator(ch) && ch != ' ') {
				temp = temp * 10 + ch - '0';
				ch = str[i++];
			}
			num_stack.push(temp);  //��ֵ��ջ
		}
	}
	/*���ʽ�����ˣ���Ϊ�����Ⱥ��ˣ��������ջҲ��ջ���ˣ�ֻʣջ�׵ĵȺ��ˣ���
	���������ڲ�����ջ��*/
	exp_result = num_stack.get_top();
	return true;
}
