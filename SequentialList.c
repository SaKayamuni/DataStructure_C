/*
still have problem. 
*/
#include<stdio.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 100
typedef int Status;
typedef struct{
	int *elem ;//存储空间的基地址 
	int length ;//当前长度 
}SqList;//SqList是变量类型；
//初始化顺序表，构造长度为空的顺序表L 
Status InitList_Sq(SqList *L){
	//L->elem = new int[MAXSIZE];c语言不支持new 
	L->elem = (int)malloc(sizeof(int)*MAXSIZE); 
	if(!L->elem) exit(OVERFLOW);
	L->length = 0 ;
	return OK ;
}
//销毁顺序表
Status DestroyList_Sq(SqList *L){
	if(L != NULL){
		free(L);
		return OK;	
	}
	return ERROR;
}
//清空顺序表
Status ClearList_Sq(SqList *L){
	int i;
	if(L->length != 0){
		for(i=L->length-1;i>0;i--){
			L->elem[i-1] = L->elem[i];
			--L->length;
		} 
		return OK;
	}
	return ERROR;
	
}
//判断顺序表是否为空
Status ListEmpty_Sq(SqList L){
	if(L.length == 0) return OK;
	else return ERROR;
}
//计算顺序表长度
Status ListLength(SqList L){
	int len = L.length;
	return len;
}
//返回第i个数据元素的值
Status GetElem(SqList L,int i,int *e){
	*e = L.elem[i-1];
	return e;
}
//按值查找
Status LocateElem_Sq(SqList L,int e){
	int i;
	for(i=0;i<L.length;i++)
	{
		if(L.elem[i]==e) 
			return i+1;
	}
	return 0;
} 
//返回前驱
Status PriorElem(SqList L,int cur_e){
	int i;
	for(i=0;i<L.length;i++){
		if(L.elem[i] == cur_e){
			if(i==0 ||i==L.length-1 ) 
				return ERROR;
			else {
				return L.elem[i-1];
			}
		}
	}
}
//返回后继
Status NextElem(SqList L,int cur_e){
	int i;
	for(i=0;i<L.length;i++){
		if(L.elem[i] == cur_e){
			if(i == L.length-1 ) 
				return ERROR;
			else {
				return L.elem[i+1];
			}
		}
	}
} 
//顺序表的插入
Status ListInsert_Sq(SqList *L,int i,int e){
	int j;
	if(i<1||i>L->length+1) return ERROR;
	if(L->length==MAXSIZE) return ERROR;
	for(j=L->length-1;j>=i-1;j--){
		L->elem[j+1]=L->elem[j];
	}
	L->elem[i-1]=e;
	++ L->length;
	return OK;
} 
//删除表中第i个数据元素 
Status ListDelete_Sq(SqList *L,int i,int *e){
	int j;
	if( i<1 || i>L->length) return ERROR ;
	e = L->elem[i-1];
	printf(" %d has been deleted",e); 
	for(j=i;j<=L->length-1;j++){
		L->elem[j-1]= L->elem[j];
	}
	--L->length;
	return OK;
}
void PrintList_Sq(SqList L){
	int i;
	for(i=0;i <= (L.length-1);i++){
		printf("%d\n",L.elem[i]);
	}
}
int main(void)
{
	int flag;
	int *val;
	int elemLocation;
	SqList A;
	InitList_Sq(&A);
	flag = ListEmpty_Sq(A);
	if(flag == 0) printf("List is not empty\n");
	else printf("List is empty\n");
	ListInsert_Sq(&A,1,1);
	ListInsert_Sq(&A,2,2);
	ListInsert_Sq(&A,3,3);
	ListInsert_Sq(&A,4,4);
	ListInsert_Sq(&A,5,5);
	PrintList_Sq(A);
	flag = ListDelete_Sq(&A,5,val);
	if(flag == 0) printf("Delete error\n");
	else printf("Delete Success.\n",val);//出错。 
	PrintList_Sq(A);
	elemLocation = LocateElem_Sq(A,4);
	printf("4 is the %dth number\n",elemLocation);
	DestroyList_Sq(&A);
	return 0;
}
 
