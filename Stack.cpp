#include<iostream>
#include"Stack.h"
using namespace std;

//·ûºÅÕ»Æ¥Åä²Ù×÷
int InitStack(LinkStack &S){		//³õÊ¼»¯
	S = NULL;
	return 0;
}

int Push(LinkStack &S, char e){	//ÈëÕ»
	LinkStack p = new StackNode;
	p = new StackNode;
	p->data = e;
	p->next = S;
	S = p;
	return 0;
}

bool Pop(LinkStack &S, char &e){	//³öÕ»
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

char GetTop(LinkStack S){		//È¡Õ»¶¥
	if (S != NULL)
		return S->data;
	else
		return NULL;
}