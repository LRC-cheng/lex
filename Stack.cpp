#include<iostream>
#include"Stack.h"
using namespace std;

//����ջƥ�����
int InitStack(LinkStack &S){		//��ʼ��
	S = NULL;
	return 0;
}

int Push(LinkStack &S, char e){	//��ջ
	LinkStack p = new StackNode;
	p = new StackNode;
	p->data = e;
	p->next = S;
	S = p;
	return 0;
}

bool Pop(LinkStack &S, char &e){	//��ջ
	LinkStack p = new StackNode;
	p = new StackNode;
	if (S == NULL){
		cout << "ERROR!" << endl;
		return false;
	}
	e = S->data;
	p = S;
	S = S->next;
	delete p;
	return true;
}

char GetTop(LinkStack S){		//ȡջ��
	if (S != NULL)
		return S->data;
	else
		return NULL;
}