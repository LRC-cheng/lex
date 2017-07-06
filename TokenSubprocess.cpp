#include"TokenSubprocess.h"

char id(char ch){
	switch (ch){
	case '_':case 'a':case 'b':case 'c':case 'd':case 'e':case 'f':case 'g':case 'h':
	case 'i':case 'j':case 'k':case 'l':case 'm':case 'n':case 'o':case 'p':case 'q':
	case 'r':case 's':case 't':case 'u':case 'v':case 'w':case 'x':case 'y':case 'z':

	case 'A':case 'B':case 'C':case 'D':case 'E':case 'F':case 'G':case 'H':case 'I':
	case 'J':case 'K':case 'L':case 'M':case 'N':case 'O':case 'P':case 'Q':case 'R':
	case 'S':case 'T':case 'U':case 'V':case 'W':case 'X':case 'Y':case 'Z':

	case '1':case '2':case '3':case '4':case '5':
	case '6':case '7':case '8':case '9':case '0':
		return ch;
	default:
		return '#';
	}
}
bool word(char ch){
	switch (ch){
		//·Ö¸ô·ûºÅ
	case '\0':case '\t':case '\v':case ' ':case '\f':case '\n':case '+':
	case '-':case '*':case '/':case '(':case ')':case '[':case ']':case '{':
	case '}':case ',':case ':':case ';':case '>':case '<':case '=':case '!':
		return false;
	default:
		return true;
	}
}
int number(char ch){
	switch (ch){
	case '1':	return 1;
	case '2':	return 2;
	case '3':	return 3;
	case '4':	return 4;
	case '5':	return 5;
	case '6':	return 6;
	case '7':	return 7;
	case '8':	return 8;
	case '9':	return 9;
	case '0':	return 0;
	default:		return -1;
	}
}