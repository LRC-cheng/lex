#pragma once
#include<string>
using namespace std;
/*´íÎóÐÅÏ¢¼ÇÂ¼*/
class WrongMessage{
public:
	int getType(){
		return type;
	}
	void setType(int _type){
		type = _type;
	}
	int getLocation(){
		return location;
	}
	void setLocation(int _location){
		location = _location;
	}
	string getName(){
		return name;
	}
	void setName(char *_name){
		name = _name;
	}
private:
	int type;
	int location;
	string name;
};