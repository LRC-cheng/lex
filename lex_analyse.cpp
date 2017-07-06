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

//�ʷ���������
cpp_token* cpp_direct_start(char *cpp_direct, int len, int &count){
	int length = len;			//�ı�����
	int i = 0, j = 0;		//j:��������i:���ٶ�ȡ����
	int k = 0, value = 0;				//k������������
	int line = 1;
	cpp_token *token = new cpp_token[MAX];
	//ָ��ǰ��ȡλ�� �հ׷����� ��|��\t��|'\v'|'\0'|'\f'|'\n'
	char *p;
	char *buf;
	p = cpp_direct;
	while (i <= length){
		switch (*p){

			//�հ׷���
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

			//����
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


			//ȷ��Ϊ��ʶ��
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

			//����������ָ���
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
		//�ж��Ǳ�ʶ�����Ǳ�����
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

	char A[7] = { '{', '}', '[', ']', '(', ')', '0' };	//����һ���������飬���ڲ��ұȽϡ�0��Ϊһ�����
	while (cfile.get(ch))
	{
		cpp_direct_read[i++] = ch;

		//����ƥ�乤��
		if (ch == '\n'){ count++; }

		if (ch == '[' || ch == '{' || ch == '('){//�������ŵ���ջ
			Push(S, ch);
		}
		if (ch == ']' || ch == '}' || ch == ')'){
			for (int j = 0; j < 6; j++){	//����ch�����������λ��A[k]
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
	cout << "�ѷ���BUG" << wrongMessageNum << "����" << endl;
	for (int i = 0; i <= wrongMessageNum; i++){
		if (wrongMessage[i].getType() == -1){
			cout << "[C0001]:ERROR:�������ڲ��Ϸ������֣�\"" << wrongMessage[i].getName() << "\",����" << wrongMessage[i].getLocation() << "��" << endl;
		}
		if (wrongMessage[i].getType() == -2){
			cout << "[C0002]:ERROR:�������ڲ��Ϸ��ı�ʶ����\"" << wrongMessage[i].getName() << "\",����" << wrongMessage[i].getLocation() << "��" << endl;
		}
		if (wrongMessage[i].getType() == -3){
			cout << "[C0003]:ERROR:��������ƥ����󣬼���" << wrongMessage[i].getLocation() << "��" << endl;
		}
	}
	cout << endl << endl;
}

/*�﷨��������

*/
int grammer(cpp_token *token, int num){

}

int main(){
	//��������ı�
	char *cpp_direct_read;
	cpp_direct_read = new char[MAX];
	cpp_direct_read[0] = '\0';

	int count = 1;
	int i = 0;
	int g_result = 0;

	cpp_direct_read = ReadCpp(cpp_direct_read, i, count);

	cout << "����Դ����" << endl << endl;
	cout << cpp_direct_read << endl;

	cout << endl;
	cout << "----------��ʼ���дʷ�����----------" << endl;
	cout << endl;

	token = cpp_direct_start(cpp_direct_read, i, count);		//��ʼ����
	Result(token, count);

	/*
	cout << endl;
	cout << "-----------��ʼ�����﷨����-------------" << endl;
	cout << endl;

	g_result = grammer(token, count);
	if (g_result == -1){
		cout << "���﷨����û��ƥ����﷨" << endl;
	}
	else{
		cout << "ƥ��ɹ���"<<endl;
	}
	*/
	system("pause");
	return 0;
}