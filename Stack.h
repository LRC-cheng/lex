#ifndef STACK_H
#define STACK_H

typedef struct StackNode{
	char data;
	struct StackNode *next;
}StackNode, *LinkStack;

int InitStack(LinkStack &);		//初始化
int Push(LinkStack &, char);	//入栈
bool Pop(LinkStack &, char &);	//出栈
char GetTop(LinkStack);		//取栈顶

#endif