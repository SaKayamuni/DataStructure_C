#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;//status 是函数返回值类型，其值是函数状态结果代码。 
typedef int Elemtype;
 
#define MAXSIZE 100
struct Book {
	string id;//ISBN
	string name;//书名
	double price;//价格
	string author;//作者 
}; 

typedef struct LNode {
	Book data;//数据域
	struct LNode *next;//节点的指针域 
} LNode,*LinkList;

string head_1,head_2,head_3,head_4;
int length;

Status InitList_L(LinkList &L) { //算法2.6 单链表的初始化
	//构造空链表L 
	L = new LNode;
	L->next = NULL;
	return OK;
}

Status GetElem_L(LinkList L,int i,Book &e) { //算法2.7 单链表的取值 
	//在带头节点的单链表L中查找第i个元素
	//用e返回第i个元素的值
	int j;
	LinkList p;
	p = L->next;
	j = 1;//初始化，p指向第一个节点，j为计数器
	while(j<i && p) {
		p = p->next;
		++j;
	} 
	if(!p || j>i) 
		return ERROR;
	e = p->data;
	return OK;
}  

LNode *LocateElem_L(LinkList L,double e) { //算法2.8 按值查找 
	//在带头节点的单链表L中查找值为e的元素
	LinkList p;
	p = L->next;
	while(p && p->data.price != e)
		p = p->next;
	return p; 
}

Status ListInsert_L(LinkList &L, int i,Book &e) { //  算法2.9 单链表的插入 
	int j;
	LinkList p,s;
	p = L ;
	while(p && j<i-1 ) {
		p = p->next;
		++j;
	} //p指向i-1个节点。
	s = new LNode;
	s->data = e ;
	s->next = p->next;
	p->next = s;
	++length;
	return OK; 
}

Status ListDelete_L(LinkList &L,int i) { // 算法2.10 单链表的删除 
	LinkList p,q;
	int j ;
	p = L ;
	j = 0 ;
	while((p->next) && ( j<i-1 )) {
		p = p->next;
		++j;
	}
	if(!(p->next) || (j > i-1 ))
		return ERROR;
	q = p->next;
	p->next = q->next;
	delete q;
	--length;
	return OK;
}

void CreateList_H(LinkList &L,int n) { //算法2.11 前插法创建单链表 
	LinkList p;
	L = new LNode;
	L->next = NULL;
	length = 0;
	fstream file;
	file.open("book.txt");
	if(!file) {
		cout << "未找到文件，无法打开！" << endl;
		exit(ERROR); 
	} 
	file >> head_1 >>head_2>>head_3>>head_4;
	while(!file.eof()) {
		p = new LNode;
		file>> p->data.id>>p->data.name>>p->data.price>>p->data.author;
		p->next = L->next;
		L->next = p;
		length++;
	}
	file.close();
}
 
 void CreateList_R(LinkList &L,int n) { // 算法2.12 后插法 
 	LinkList p,r;
	L = new LNode;
	L->next = NULL;
	r = L;//尾指针指向头节点
	length = 0;
	fstream file;
	file.open("book.txt");
	if(!file) {
		cout << "未找到文件，无法打开！" << endl;
		exit(ERROR); 
	} 
	file >> head_1 >>head_2>>head_3>>head_4;
	while(!file.eof()) {
		p = new LNode;
		file>> p->data.id>>p->data.name>>p->data.price>>p->data.author;
		p->next = NULL;
		r->next = p;
		r = p ;
		length++;
	}  
	file.close();
 }
 
 int main() {
 	int a,n,choose;
 	double price;
 	Book e;
 	LinkList L,p;
 	cout << "1.建立\n";
	cout << "2.输入\n";
	cout << "3.取值\n";
	cout << "4.查找\n";
	cout << "5.插入\n";
	cout << "6.删除\n";
	cout << "7.输出\n";
	cout << "0.退出\n\n";
	
	choose = -1;
	while(choose !=0 ) {
		cout<<"请选择：";
		cin >> choose;
		switch(choose) {
			case 1: //建立一个单链表
				if (InitList_L(L))
					cout << "成功建立链表\n\n";
				else
					cout << "建立链表失败\n\n";
				break;
			case 2: //后插法创建单链表
				CreateList_R(L,length);
				cout << "输入book.txt 信息完毕\n\n";
				break;
			case 3: //单链表按序号取值
				cout << "请输入一个位置用来取值";
				cin >> a;
				if(GetElem_L(L,a,e)) {
					cout << "查找成功\n";
					cout <<"第"<<a<<"本图书的信息是：\n";
					cout << left << setw(15) << e.id <<"\t"<< left <<setw(50)
							<< e.name << "\t" << left << setw(5) <<e.price << left << setw(6) << e.author <<endl
							<< endl;
				} else
					cout << "查找失败\n\n";
				break;
			case 4://单链表的按值查找 
				cout << "请输入所要查找价格：";
				cin >> price;
				if(LocateElem_L(L,price) != NULL) {
					cout << "查找成功\n";
					cout <<"该价格对应的书名为："<< LocateElem_L(L,price)->data.name 
					<< endl << endl;
				} else
					cout<<"查找失败\n\n";
				break;	
			case 5: //单链表的插入 
				cout << "请输入插入的位置和书本信息，包括：编号 书名 价格 作者（用空格隔开）：";
				cin >> a;
				cin >> e.id >> e.name >> e.price >> e.author;
				if(ListInsert_L(L,a,e))
					cout << "插入成功.\n\n";
				else
					cout <<"插入失败.\n\n";
				break;
			case 6: //单链表的删除 
				cout << "请输入要删除书籍的位置：";
				cin>>a;
				if(ListDelete_L(L,a))
					cout << "删除成功.\n\n";
				else
					cout << "删除失败.\n\n";
				break;
			case 7://单链表的输出
				cout << "当前图书系统信息（链表）读出： \n";
				p = L->next;
				while(p) {
					cout << left << setw(15) << p->data.id <<"\t"<<left
							<<setw(50) <<p->data.name << "\t" <<left
							<<setw(5)<<p->data.price <<"\t"<< left << setw(6) <<p->data.author<< endl;
					p = p->next; 
				}
				cout << endl;
				break;	 
		} 
	}
	
	return 0;
 }
 
 
 
 
 
