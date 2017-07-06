#include<iostream>
#include<stdio.h>
#include<fstream>
#include<string>
#include"UserID.h"
#include"WrongMassage.h"
#include"Cpp_Token.h"
#include"Stack.h"
#include"head.h"
#include"TokenSubprocess.h"
#include<stack>
#define MAX 100000 

using namespace std;

static int User_ID = 0;
WrongMessage *wrongMessage = new WrongMessage[1000];
static int wrongMessageNum = 0;
cpp_token *token = new cpp_token[100000];

void _isNumber(char *buf, cpp_token *token, int &line);
void _isID(char *buf, cpp_token *token, int &line);
void _IDtype(char *buf, cpp_token *token);

char*ReadCpp(char *cpp_direct_read, int &i, int &count);
void Result(cpp_token *token, int count);


int grammer(cpp_token *token, int num);

//词法分析过程
cpp_token* cpp_direct_start(char *cpp_direct, int len, int &count){
	int length = len;			//文本长度
	int i = 0, j = 0;		//j:单词数，i:跟踪读取进度
	int k = 0, value = 0;				//k：缓冲区读条
	int line = 1;
	cpp_token *token = new cpp_token[MAX];
	//指向当前读取位置 空白符：‘ ’|‘\t’|'\v'|'\0'|'\f'|'\n'
	char *p;
	char *buf;
	p = cpp_direct;
	while (i <= length){
		switch (*p){

			//空白符：
		case '\0':
		case '\t':
		case '\v':
		case ' ':
		case '\f':
			p++; i++;
			break;
		case'\n':
			p++; i++; line++;
			break;

			//数字
		case '1':case '2':case '3':case '4':case '5':
		case '6':case '7':case '8':case '9':case '0':
			buf = new char[50];
			buf[0] = ' ';
			token[j].sy1 = INT;
			k = 0;
			while (word(*p)){
				buf[k++] = *p;
				p++; i++;
			}
			buf[k] = '\0';
			_isNumber(buf, &token[j], line);
			j++;
			delete[]buf;
			break;


			//确定为标识符
		case '_':case 'a':case 'b':case 'c':case 'd':case 'e':case 'f':case 'g':case 'h':
		case 'i':case 'j':case 'k':case 'l':case 'm':case 'n':case 'o':case 'p':case 'q':
		case 'r':case 's':case 't':case 'u':case 'v':case 'w':case 'x':case 'y':case 'z':

		case 'A':case 'B':case 'C':case 'D':case 'E':case 'F':case 'G':case 'H':case 'I':
		case 'J':case 'K':case 'L':case 'M':case 'N':case 'O':case 'P':case 'Q':case 'R':
		case 'S':case 'T':case 'U':case 'V':case 'W':case 'X':case 'Y':case 'Z':
			buf = new char[50];
			buf[0] = ' ';
			token[j].sy1 = ID;
			k = 0;
			do{
				buf[k++] = *p;
				p++; i++;
			} while (word(*p));
			buf[k] = '\0';
			_isID(buf, &token[j], line);
			j++;
			delete[]buf;

			break;

			//分析运算符分隔符
		case ':':
			token[j].sy1 = COLON;
			p++; i++; j++;
			break;

		case '&':
			token[j].sy1 = AND;
			p++; i++; j++;
			break;
		}
	}
	count = j;
	return token;
}
void _isNumber(char *buf, cpp_token *token, int &line){
	char *p;
	int value = 0;
	p = buf;
	int a = 0;
	do{
		value = value * 10 + number(*p);
		p++;
		a = number(*p);
	} while (*p != '\0'&& a >= 0);
	if (*p == '\0'){
		token->val = value;
		token->sy1 = card[value];
	}
	else{
		token->sy1 = ERROR_A;
		token->val = line;
		wrongMessage[wrongMessageNum].setType(ERROR_A);
		wrongMessage[wrongMessageNum].setLocation(line);
		wrongMessage[wrongMessageNum].setName(buf);
		wrongMessageNum++;
	}

}
void _isID(char *buf, cpp_token *token, int &line){
	char *p;
	char *value;
	string str;
	char a;
	value = new char[50];
	int count = 0;
	value[0] = '\0';
	p = buf;
	do{
		value[count] = id(*p);
		p++; count++;
		a = id(*p);
	} while (a != '#');
	value[count] = '\0';
	if (*p == '\0'){
		//判断是标识符还是保留字
		_IDtype(buf, token);
	}
	else{
		token->sy1 = ERROR_B;
		token->val = line;
		wrongMessage[wrongMessageNum].setType(ERROR_B);
		wrongMessage[wrongMessageNum].setLocation(line);
		wrongMessage[wrongMessageNum].setName(buf);
		wrongMessageNum++;
	}
	delete[]value;
}
void _IDtype(char *buf, cpp_token *token){
	for (int m = 0; m < 10; m++){
		if (!strcmp(syswords[m], buf)){
			token->sy1 = sysVal[m];
			return;
		}
	}
	token->val = User_ID;
	_UserId[User_ID].setName(buf);
	User_ID++;
	return;
}

char*ReadCpp(char *cpp_direct_read,int &i ,int &count){

	LinkStack S;
	InitStack(S);
	int k;
	char ch, x;

	ifstream cfile("process.txt", ios::in);

	char A[7] = { '{', '}', '[', ']', '(', ')', '0' };	//定义一个括号数组，用于查找比较‘0’为一个标记
	while (cfile.get(ch))
	{
		cpp_direct_read[i++] = ch;

		//符号匹配工作
		if (ch == '\n'){ count++; }

		if (ch == '[' || ch == '{' || ch == '('){//属于括号的入栈
			Push(S, ch);
		}
		if (ch == ']' || ch == '}' || ch == ')'){
			for (int j = 0; j < 6; j++){	//查找ch在括号数组的位置A[k]
				if (ch == A[j]){
					k = j;
					break;
				}
			}
			x = GetTop(S);
			if (x == A[k - 1]){
				Pop(S, x);
			}
			else{
				wrongMessage[wrongMessageNum].setType(ERROR_C);
				wrongMessage[wrongMessageNum].setLocation(count);
				wrongMessageNum++;
			}
		}
	}
	if (!GetTop(S)){
	}
	else{
		wrongMessage[wrongMessageNum].setType(ERROR_C);
		wrongMessage[wrongMessageNum].setLocation(count);
		wrongMessageNum++;
	}
	cpp_direct_read[i] = '\0';

	return cpp_direct_read;
}
void Result(cpp_token *token,int count){
	char *type[50] = { "ERROR", "+", "-", "*", "/",
		"(", ")", "[", "]", "{", "}", ",", ":",
		";", ">", "<", "=", ">=", "<=", "==", "!=", "+=", "!", "." };

	for (int i = 0; i < count; i++){
		cout << "( ";
		if (token[i].sy1 == -3){
			cout << "ERROR";
			cout << " , ";
			cout << token[i].val;
		}
		else if (token[i].sy1 == -2){
			cout << "ERROR";
			cout << " , ";
			cout << token[i].val;
		}
		else if (token[i].sy1 == -1){
			cout << "ERROR";
			cout << " , ";
			cout << token[i].val;
		}
		else if (token[i].sy1 <10){
			cout << syswords[token[i].sy1];
			cout << " , ";
			cout << "_";
		}
		else if (token[i].sy1 < 99){
			cout << "operater";
			cout << " , ";
			cout << type[token[i].sy1 - 20];
		}
		else if (token[i].sy1 == 100){
			cout << "ID";
			cout << " , ";
			cout << _UserId[token[i].val].getName();
		}
		else if (token[i].sy1 == 101){
			cout << "number";
			cout << " , ";
			cout << token[i].val;
		}
		cout << " )" << endl;
	}

	cout << endl << endl;
	cout << "已发现BUG" << wrongMessageNum << "处：" << endl;
	for (int i = 0; i <= wrongMessageNum; i++){
		if (wrongMessage[i].getType() == -1){
			cout << "[C0001]:ERROR:出错，存在不合法的数字：\"" << wrongMessage[i].getName() << "\",见第" << wrongMessage[i].getLocation() << "行" << endl;
		}
		if (wrongMessage[i].getType() == -2){
			cout << "[C0002]:ERROR:出错，存在不合法的标识符：\"" << wrongMessage[i].getName() << "\",见第" << wrongMessage[i].getLocation() << "行" << endl;
		}
		if (wrongMessage[i].getType() == -3){
			cout << "[C0003]:ERROR:出错，括号匹配错误，见第" << wrongMessage[i].getLocation() << "行" << endl;
		}
	}
	cout << endl << endl;
}

/*语法分析过程

*/
int grammer(cpp_token *token, int num){

}

int main(){
	//保存程序文本
	char *cpp_direct_read;
	cpp_direct_read = new char[MAX];
	cpp_direct_read[0] = '\0';

	int count = 1;
	int i = 0;
	int g_result = 0;

	cpp_direct_read = ReadCpp(cpp_direct_read, i, count);

	cout << "输入源代码" << endl << endl;
	cout << cpp_direct_read << endl;

	cout << endl;
	cout << "----------开始进行词法分析----------" << endl;
	cout << endl;

	token = cpp_direct_start(cpp_direct_read, i, count);		//开始处理
	Result(token, count);

	/*
	cout << endl;
	cout << "-----------开始进行语法分析-------------" << endl;
	cout << endl;

	g_result = grammer(token, count);
	if (g_result == -1){
		cout << "有语法错误，没有匹配的语法" << endl;
	}
	else{
		cout << "匹配成功！"<<endl;
	}
	*/
	system("pause");
	return 0;
}