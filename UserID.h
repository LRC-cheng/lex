#pragma once
#include<string>
using namespace std;
//用户标识符
class UserId{
public:
	UserId(){
		Val++;
		num = Val;
	};
	void setName(char *name){
		Name = name;
	}
	string getName(){
		return Name;
	}
	int getNum(){
		return num;
	}
private:
	string Name;
	int num;
	static int Val;
};
int UserId::Val = 0;
UserId *_UserId = new UserId[1000];