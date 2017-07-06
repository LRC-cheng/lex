#pragma once
//预先定义符号、关键词
#define ERROR_C -3
#define ERROR_B -2
#define ERROR_A -1
#define WHITE 0

#define CARD_2 2
#define CARD_3 3
#define CARD_4 4
#define CARD_5 5
#define CARD_6 6
#define CARD_7 7
#define CARD_8 8
#define CARD_9 9
#define CARD_10 10
#define CARD_J 11
#define CARD_Q 12
#define CARD_K 13
#define CARD_A 14
#define Spade 15
#define Heart 16
#define Club 17
#define Diamond 18
#define Pass 19
#define begin 20
#define end 21
#define COLON 22
#define AND 23


#define STRING 50

//语法分析
#define ID 100
#define INT 101

int card[10] = { WHITE, 1, CARD_2, CARD_3, CARD_4, CARD_5, CARD_6,CARD_7, CARD_8, CARD_9 };
char *syswords[10] = { " ", "Spade", "Heart", "Club", "Diamond", "Pass", "begin", "end", "COLON", "AND" };
int sysVal[10] = { WHITE, Spade, Heart, Club, Diamond, Pass, begin, end, COLON, AND };
