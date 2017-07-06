#ifndef STACK_H
#define STACK_H

typedef struct StackNode{
	char data;
	struct StackNode *next;
}StackNode, *LinkStack;

int InitStack(LinkStack &);		//��ʼ��
int Push(LinkStack &, char);	//��ջ
bool Pop(LinkStack &, char &);	//��ջ
char GetTop(LinkStack);		//ȡջ��

#endif