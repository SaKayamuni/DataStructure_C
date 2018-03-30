#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;//status �Ǻ�������ֵ���ͣ���ֵ�Ǻ���״̬������롣 
typedef int Elemtype;
 
#define MAXSIZE 100
struct Book {
	string id;//ISBN
	string name;//����
	double price;//�۸�
	string author;//���� 
}; 

typedef struct {
	Book *elem;//�洢�ռ�Ļ���ַ��
	int length;//��ǰ���� 
} SqList;

Status InitList_Sq(SqList &L){ //�㷨2.1 ˳���ĳ�ʼ��
	//����һ���յ�˳���L 
	L.elem = new Book[MAXSIZE];
	if(!L.elem)
		exit(OVERFLOW);
	L.length = 0;
	return OK;	
} 

Status GetElem(SqList L, int i,Book &e) { //�㷨2.2 ˳����ȡֵ  
	if(i < 1 || i > L.length)
		return ERROR;
	e = L.elem[i-1];
	return OK; 
}

int LocateElem_Sq(SqList L, double e) { //�㷨2.3 ˳���Ĳ��� 
	for(int i = 0;i<L.length;i++){
		if(L.elem[i].price == e){
			return i+1;
		}
	}
	return 0; 
}

Status ListInsert_Sq(SqList &L, int i,Book e) { //�㷨2.4 ˳���Ĳ���
	//��˳���L�е�i��λ��ǰ�����µ�Ԫ��
	//iֵ�Ϸ���Χ�� 1<=i<=L.length
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

Status ListDelete_Sq(SqList &L, int i) { //�㷨2.5 ˳����ɾ��
	//��˳���L��ɾ����i��Ԫ�أ�����e������ֵ
	//iֵ�Ϸ���Χ�� 1<=i<=L.length 
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
	cout << "1.����\n";
	cout << "2.����\n";
	cout << "3.ȡֵ\n";
	cout << "4.����\n";
	cout << "5.����\n";
	cout << "6.ɾ��\n";
	cout << "7.���\n";
	cout << "0.�˳�\n\n";
	choose = 100;
	while (choose != 0) {
		cout << "��ѡ��";
		cin >>choose;
		switch (choose) {
			case 1://����˳���
				if(InitList_Sq(L))
					cout << "�ɹ�����˳���\n\n";
				else
					cout << "˳�����ʧ��\n\n";
				break;
			case 2:{ //˳�����Ϣ����
				i = 0;
				L.elem = new Book[MAXSIZE];
				if (!L.elem)
					exit(OVERFLOW);
				L.length = 0;
				fstream file;
				file.open("book.txt");
				if (!file) {
					cout << "����δ�ҵ��ļ���" << endl;
					exit(ERROR); 
				} 
				file >> head_1 >> head_2 >> head_3 >> head_4 ;
				while (!file.eof()) {
					file >> L.elem[i].id >> L.elem[i].name >>L.elem[i].price>>L.elem[i].author;
					i++;
				}
				cout << "����book.txt ��Ϣ���\n\n";
				L.length = i;
				file.close();
			}
				break;
			case 3://˳����ȡֵ
				cout << "������һ��λ����ȡֵ��\n";
				cin>>i;
				temp = GetElem(L,i,e);
				if(temp != 0 ) {
					cout << "���ҳɹ�\n";
					cout << "��" << i << "��ͼ�����Ϣ�ǣ� \n";
					cout << left << setw(15) << e.id <<"\t"<< left <<setw(50)
							<< e.name << "\t" << left << setw(5) <<e.price << left << setw(6) << e.author <<endl
							<< endl;
				} else
					cout<<"����ʧ�ܣ�λ�ó�����Χ\n\n";
				break;
			case 4://˳���Ĳ���
				cout << "��������Ҫ���ҵļ۸� ";
				cin >> price;
				temp = LocateElem_Sq(L,price);
				if(temp != 0 ) {
					cout << "���ҳɹ�\n";
					cout << "�ü۸��Ӧ������Ϊ�� "<< L.elem[temp-1].name <<endl <<endl; 
				} else
					cout << "����ʧ�ܣ�û������۸��Ӧ���鼮\n\n";
				break;
			case 5:
				cout << "����������λ�ú��鱾��Ϣ����������� ���� �۸� ���ߣ��ÿո��������";
				cin >> a;
				cin >> e.id >> e.name >> e.price >> e.author;
				if(ListInsert_Sq(L,a,e))
					cout << "����ɹ�.\n\n";
				else
					cout <<"����ʧ��.\n\n";
				break;
			case 6://˳����ɾ��
				cout << "������Ҫɾ�����鼮��λ�ã�";
				cin>>c;
				if(ListDelete_Sq(L,c))
					cout << "ɾ���ɹ�.\n\n";
				else
					cout << "ɾ��ʧ��.\n\n";
				break;
			case 7://˳�������
				cout << "��ǰͼ��ϵͳ��Ϣ��˳��������� \n";
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






