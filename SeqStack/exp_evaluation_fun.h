using namespace std;  //否则cout, endl报错

//计算表达式的具体函数
char ops[7] = { '+', '-', '*', '/', '(', ')', '=' };
//
/*
运算符优先级的比较矩阵，op1是运算符栈栈顶元素，op2是正在读入的运算符
N表示在正确的表达式中不会出现此种情况
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

//1.判断字符ch是否为运算符
bool is_operator(char ch);
//2.比较运算符ch1和ch2的优先级
char compare(char ch1, char ch2);
//3.计算表达式 z = x <op> y ，注意除数不为0
bool compute(double x, char op, double y, double &z);
//4.计算表达式的值
bool compute_exp(char *str, double &result);

//1.判断字符ch是否为运算符
bool is_operator(char ch) {
	int i = 0;
	for (i = 0; i < 7; i++) {
		if (ch == ops[i])
			return true;
	}
	return false;
}

//2.比较运算符ch1和ch2的优先级（ch1在栈顶，ch2是正在读入的运算符）
char compare(char ch1, char ch2) {
	int i, p1, p2;  //m,n用于确定ch1和ch2在矩阵中的位置
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

//3.计算表达式 z = x <op> y ，注意除数不为0
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
			cout << "除数为0，出错！" << endl;
			return false;
		}
	}
	return true;
}

//4.计算表达式的值
bool compute_exp(char *str, double &exp_result) {
	char ch = ' ';  //存放读入的字符
	int temp = 0;  //把字符转换成数字
	char op = ' ';  //用于存放从操作符栈顶弹出的运算符，计算两个数
	double n1 = 0, n2 = 0, n3 = 0;  //从操作数栈弹出两个运算数n1，n2，计算结果n1 <op> n2存到n3里
	char priority = ' ';  //用于判断栈顶运算符和当前读入运算符的优先级
	int i = 0;  //用于遍历表达式
	SeqStack <char> op_stack(20);  //运算符栈
	SeqStack <double> num_stack(20);  //运算数栈

									  //把“=”压入栈
	op_stack.push('=');
	//读入表达式
	ch = str[i++];
	while (ch != '=' || op_stack.get_top() != '=') {  //第一部分保证把表达式读完，第二部分保证把运算符栈里的op处理完
		while (ch == ' ') {  //过滤空格
			ch = str[i++];
		}
		if (is_operator(ch)) {  //是运算符
			priority = compare(op_stack.get_top(), ch);  //判断栈顶运算符和当前运算符的优先级
			switch (priority) {
			case '<':  //当前运算符优先级高，直接入栈
				op_stack.push(ch);
				ch = str[i++];
				break;

			case '>':  //当前运算符优先级低，要先弹出栈顶的运算符做计算，算到当前运算符能
				op = op_stack.get_top();  //弹出运算符栈顶运算符
				op_stack.pop();
				n2 = num_stack.get_top();  //先弹出的操作数是第2个操作数
				num_stack.pop();
				n1 = num_stack.get_top();  //后弹出的操作数是第1个操作数
				num_stack.pop();
				if (compute(n1, op, n2, n3)) {  //计算n3 = n1 <op> n2 
					num_stack.push(n3);  //新的计算结果压入栈中
					break;
				}
				else {  //计算出错，退出程序
					exp_result = 0;
					return false;
				}

			case '=':
				/*只有当前符号为“）”，栈顶符号为“（”时，会出现此种情况，
				即前面计算的是括号里的表达式，现在表达式算完了，结果也入操作数栈里了，就剩俩空括号*/
				op_stack.pop();  //脱括号
				ch = str[i++];  //接收下一个字符
				break;
			}
		}
		else {  //当前读入的是运算数
			temp = ch - '0';  //把当前读入的字符转成数字
			ch = str[i++];  //继续往后读
			while (!is_operator(ch) && ch != ' ') {
				temp = temp * 10 + ch - '0';
				ch = str[i++];
			}
			num_stack.push(temp);  //数值入栈
		}
	}
	/*表达式读完了（因为读到等号了），运算符栈也到栈底了（只剩栈底的等号了），
	运算结果就在操作数栈中*/
	exp_result = num_stack.get_top();
	return true;
}
