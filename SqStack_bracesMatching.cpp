/*

����ƥ�� 
*/ 

#include<iostream>
#include<fstream>
using namespace std;

//˳��ջ����
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE  100//˳��ջ�洢�ռ�ĳ�ʼ������
typedef int Status;
typedef char SElemType;

typedef struct {
	SElemType *base;//ջ��ָ��
	SElemType *top;//ջ��ָ��
	int stacksize;//ջ���õ��������
} SqStack;

//�㷨3.1��˳��ջ�ĳ�ʼ��
Status InitStack(SqStack &S) {
	//����һ����ջS
	S.base = new SElemType[MAXSIZE];//Ϊ˳��ջ��̬����һ���������ΪMAXSIZE������ռ�
	if (!S.base)
		exit(OVERFLOW); //�洢����ʧ��
	S.top = S.base; //top��ʼΪbase����ջ
	S.stacksize = MAXSIZE; //stacksize��Ϊջ���������MAXSIZE
	return OK;
}
//�㷨3.2��˳��ջ����ջ
Status Push(SqStack &S, SElemType e) {
	// ����Ԫ��eΪ�µ�ջ��Ԫ��
	if (S.top - S.base == S.stacksize)
		return ERROR; //ջ��
	*(S.top++) = e; //Ԫ��eѹ��ջ����ջ��ָ���1
	return OK;
}
//�㷨3.3��˳��ջ�ĳ�ջ
Status Pop(SqStack &S, SElemType &e) {
	//ɾ��S��ջ��Ԫ�أ���e������ֵ	
	if (S.base == S.top)
		return ERROR;//ջ��
	e = *(--S.top); //ջ��ָ���1����ջ��Ԫ�ظ���e
	return OK;
}
//�㷨3.4��ȡ˳��ջ��ջ��Ԫ��
char GetTop(SqStack S) {//����S��ջ��Ԫ�أ����޸�ջ��ָ��
	if (S.top != S.base) //ջ�ǿ�
		return *(S.top - 1); //����ջ��Ԫ�ص�ֵ��ջ��ָ�벻��
}
//�ж�ջ�Ƿ�Ϊ��
Status StackEmpty(SqStack S) {
	if(S.top == S.base)
		return OK;
	else
		return false; 
} 

Status Matching(SqStack &S) {
	int flag = 1;
	char ch;
	char x;//ջ��Ԫ�� 
	cin>>ch;
	while((ch != 'q') && (flag)){
		switch(ch) {
			case '[' :
				Push(S,ch);
			break;
			case '(' :
				Push(S,ch);
			break;
			case ')' :
				x = GetTop(S);
				if(x == '(' ) 
					Pop(S,x);
				else
					flag = 0;
			break;
			case ']' :
				x = GetTop(S);
				if(x == '[' ) 
					Pop(S,x);
				else
					flag = 0;
			break;				 
		}
		cin>>ch;
	}
	if(StackEmpty(S) && flag) {
		return OK;
	}
	else {
		return ERROR;
	}
} 
int main() {
	SqStack s;
	InitStack(s);
	cout<<"�����룺"<<endl;
	if(Matching(s)){
		cout<<"OK\n";
	}else {
		cout<<"wrong\n";
	}
	return 0;
} 













