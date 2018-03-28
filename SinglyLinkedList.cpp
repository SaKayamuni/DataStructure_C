#include<stdio.h>
#include<malloc.h> 
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;

typedef struct LNode{
	int data;
	struct LNode *next;
}LNode , *LinkList;//LNode:����ڵ�ָ�������LinkList��ͷָ�롣 

Status InitList(LinkList &Lhead){
	Lhead = (LNode*)malloc(sizeof(LNode));
	if(Lhead == NULL) return ERROR;
	Lhead->next = NULL;
	return OK;
}
//ͷ�巨 
Status CreatList_F(LinkList Lhead,int e){
	LNode *p;
	p =(LNode *)malloc(sizeof(LNode));
	if(p == NULL) return ERROR;
	p->next = Lhead->next;
	Lhead->next = p;
	p->data = e;
	
	return OK; 
}
//��ֵ���ҷ���λ�� 
/*Status LocateElem(LinkList Lhead,int e){
	int i;
	LNode *temp = Lhead->next;i=1;
    while(temp != NULL){
    	if(temp->data == e){
    		return i; 
		}
		temp = temp->next;
		i++;
	}
}*/
void PrintList(LinkList Lhead){
	LNode *temp;
	temp = Lhead->next;
	while(temp != NULL){
		printf("%d ",temp->data);
		temp = temp->next;
	}
}

int main(void)
{
	
	int flag;
	LinkList A;
	flag = InitList(A);
	printf("%d\n",flag);
	CreatList_F(A,1);
	CreatList_F(A,2);
	CreatList_F(A,3);
	CreatList_F(A,4);
	CreatList_F(A,5);
	PrintList(A);

	free(A);
	
	return 0;
}
