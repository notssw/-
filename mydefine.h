#ifndef _MYDEFINE_H
#define _MYDEFINE_H
#include<iostream>
#include<string>
#include <algorithm>
using namespace std;
typedef struct BlockForSort {
	int x, y;	//�����հ׵��λ��
	int count;			//����������������
	int size;		//һ�������пհ׵�ĸ���
}BLFS;	//��������С�Ŀ�


bool judge(int x, int y, int i);
int getBlockNum(int x, int y);
bool cmp(BLFS& a, BLFS& b);
int writeSudokuFinality(char** final, FILE* fp);
int produceOutputIntoTxt(int produce_num);
int dealQuestion(char* path);
int dfs(int num, int size);
void setFlag(int x, int y, int i, int flag);

#endif
