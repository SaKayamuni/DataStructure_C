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

typedef struct {
	Book *elem;//存储空间的基地址。
	int length;//当前长度 
} SqList;

Status InitList_Sq(SqList &L){ //算法2.1 顺序表的初始化
	//构造一个空的顺序表L 
	L.elem = new Book[MAXSIZE];
	if(!L.elem)
		exit(OVERFLOW);
	L.length = 0;
	return OK;	
} 

Status GetElem(SqList L, int i,Book &e) { //算法2.2 顺序表的取值  
	if(i < 1 || i > L.length)
		return ERROR;
	e = L.elem[i-1];
	return OK; 
}

int LocateElem_Sq(SqList L, double e) { //算法2.3 顺序表的查找 
	for(int i = 0;i<L.length;i++){
		if(L.elem[i].price == e){
			return i+1;
		}
	}
	return 0; 
}

Status ListInsert_Sq(SqList &L, int i,Book e) { //算法2.4 顺序表的插入
	//在顺序表L中第i个位置前插入新的元素
	//i值合法范围是 1<=i<=L.length
	if(i < 1 || i > L.length)
		return ERROR;
	if(L.length == MAXSIZE)
		return ERROR;
	for(int j = L.length - 1 ; j >= i-1 ;j--){
		L.elem[j+1] = L.elem[j]; 
	} 
	L.elem[i-1] = e ;
	++L.length;
	return OK;
}

Status ListDelete_Sq(SqList &L, int i) { //算法2.5 顺序表的删除
	//在顺序表L中删除第i个元素，并用e返回其值
	//i值合法范围是 1<=i<=L.length 
	if(i < 1 || i > L.length)
		return ERROR;
	for(int j = i;j<=L.length;j++){
		L.elem[j-1] = L.elem[j];
	} 
	--L.length;
	return OK;
}

int main() {
	SqList L;
	int i = 0, temp, a, c, choose ;
	double price;
	Book e;
	string head_1,head_2,head_3,head_4;
	cout << "1.建立\n";
	cout << "2.输入\n";
	cout << "3.取值\n";
	cout << "4.查找\n";
	cout << "5.插入\n";
	cout << "6.删除\n";
	cout << "7.输出\n";
	cout << "0.退出\n\n";
	choose = 100;
	while (choose != 0) {
		cout << "请选择：";
		cin >>choose;
		switch (choose) {
			case 1://创建顺序表
				if(InitList_Sq(L))
					cout << "成功建立顺序表\n\n";
				else
					cout << "顺序表建立失败\n\n";
				break;
			case 2:{ //顺序表信息输入
				i = 0;
				L.elem = new Book[MAXSIZE];
				if (!L.elem)
					exit(OVERFLOW);
				L.length = 0;
				fstream file;
				file.open("book.txt");
				if (!file) {
					cout << "错误！未找到文件！" << endl;
					exit(ERROR); 
				} 
				file >> head_1 >> head_2 >> head_3 >> head_4 ;
				while (!file.eof()) {
					file >> L.elem[i].id >> L.elem[i].name >>L.elem[i].price>>L.elem[i].author;
					i++;
				}
				cout << "输入book.txt 信息完毕\n\n";
				L.length = i;
				file.close();
			}
				break;
			case 3://顺序表的取值
				cout << "请输入一个位置来取值：\n";
				cin>>i;
				temp = GetElem(L,i,e);
				if(temp != 0 ) {
					cout << "查找成功\n";
					cout << "第" << i << "本图书的信息是： \n";
					cout << left << setw(15) << e.id <<"\t"<< left <<setw(50)
							<< e.name << "\t" << left << setw(5) <<e.price << left << setw(6) << e.author <<endl
							<< endl;
				} else
					cout<<"查找失败！位置超出范围\n\n";
				break;
			case 4://顺序表的查找
				cout << "请输入所要查找的价格： ";
				cin >> price;
				temp = LocateElem_Sq(L,price);
				if(temp != 0 ) {
					cout << "查找成功\n";
					cout << "该价格对应的书名为： "<< L.elem[temp-1].name <<endl <<endl; 
				} else
					cout << "查找失败！没有这个价格对应的书籍\n\n";
				break;
			case 5:
				cout << "请输入插入的位置和书本信息，包括：编号 书名 价格 作者（用空格隔开）：";
				cin >> a;
				cin >> e.id >> e.name >> e.price >> e.author;
				if(ListInsert_Sq(L,a,e))
					cout << "插入成功.\n\n";
				else
					cout <<"插入失败.\n\n";
				break;
			case 6://顺序表的删除
				cout << "请输入要删除的书籍的位置：";
				cin>>c;
				if(ListDelete_Sq(L,c))
					cout << "删除成功.\n\n";
				else
					cout << "删除失败.\n\n";
				break;
			case 7://顺序表的输出
				cout << "当前图书系统信息（顺序表）读出： \n";
				for(i=0;i<L.length;i++){
					cout << left << setw(15) << L.elem[i].id <<"\t"<<left
							<<setw(50) <<L.elem[i].name << "\t" <<left
							<<setw(5)<<L.elem[i].price <<"\t"<< left << setw(6) << L.elem[i].author<< endl; 
				} 
				cout << endl;
				break;
		} 
	} 
	return 0;
}






