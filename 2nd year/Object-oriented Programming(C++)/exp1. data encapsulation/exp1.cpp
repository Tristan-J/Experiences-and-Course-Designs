#include <iostream>
#include <string.h>
#include <string>
#include <time.h>
using std::string;
using namespace std;

//Quadrangle
class Quadrangle {
public:
	virtual double area(){return -1;} 
	virtual void draw(){return;}
};
typedef Quadrangle *qPtr;

//the child classes
//Trapezoid
class Trapezoid:public Quadrangle{
private:
	string name;
	double a,b,height;
public:
	Trapezoid (double iA=1.0,double iB=2.0,double iH=2.0):name("Trapezoid"),a(iA),b(iB),height(iH){}
	double area(){
		return (a+b)*height*0.5;
	};
	void draw(){
		cout<<"\nthe name of it is:\n\t"
			<<name
			<<"\nand the factors are :\n\twidthTop="
			<<a
			<<"\n\twidthBottom="
			<<b
			<<"\n\theight="
			<<height
			<<endl;
		return;
	}
};

//Parallelogram
class Parallelogram :public Quadrangle{
private:
	string name;
	double width,height;
public:
	Parallelogram (double iA=2.0,double iH=1.0):name("Parallelogram"),width(iA),height(iH){}
	~Parallelogram () {}
	double area(){
		return width*height;
	}
	void draw(){
		cout<<"\nthe name of it is:\n\t"
			<<name
			<<"\nand the factors are :\n\twidth="
			<<width
			<<"\n\theight="
			<<height
			<<endl;
		return;
	}
};

//Rect
class Rect :public Quadrangle{
private:
	string name;
	double width,height;
public:
	Rect (double iA=2.0,double iH=1.0):name("Rectangle"),width(iA),height(iH){}
	~Rect () {}
	double area(){
		return width*height;
	}
	void draw(){
		cout<<"\nthe name of it is:\n\t"
			<<name
			<<"\nand the factors are :\n\twidth="
			<<width
			<<"\n\theight="
			<<height
			<<endl;
		return;
	}
};

//Diamond
class Diamond :public Quadrangle{
private:
	string name;
	double width,height;
public:
	Diamond (double iA=2.0,double iH=1.0):name("Diamond"),width(iA),height(iH){}
	~Diamond () {}
	double area(){
		return width*height;
	}
	void draw(){
		cout<<"\nthe name of it is:\n\t"
			<<name
			<<"\nand the factors are :\n\twidth="
			<<width
			<<"\n\theight="
			<<height
			<<endl;
		return;
	}
};

//Square
class Square :public Quadrangle {
private:
	string name;
	double a;
public:
	Square (double iA=2.0):name("Square"),a(iA){}
	~Square () {}
	double area(){
		return a*a;
	}
	void draw(){
		cout<<"\nthe name of it is:\n\t"
			<<name
			<<"\nand the factors are :\n\tborder="
			<<a
			<<endl;
		return;
	}
};

//the list and it's node
//node
class Node {
public:
	qPtr quad;
	Node *next;
	Node(){}
	~Node(){}
};

//list
class List {
protected:
	Node *head,*tail ;
	int num;
public:
	List(){
		num = 0;
		head=new Node;
		tail=head;
		tail->next=NULL;
	}
	~List() {
		Node *p=this->head;
		Node *q;
		while(p!=NULL) {
			q=p;
			p=p->next;
			delete q;
		}
	}
	void pushBack(qPtr Quad ,Node * node){
		Node *newNode = node;
		newNode->next=NULL;

		this->tail->quad = Quad;
		this->tail->next = newNode;
		this->tail=this->tail->next;
		this->num++;
		return;
	}
	void walkList (){
		Node *p =this->head;
		int NUM = 1;
		
		for (;NUM<=this->num;p=p->next){
			cout<<"-----------------------"<<NUM<<endl;
			p->quad->draw();
			cout<<"the area is :"
				<<p->quad->area()
				<<"\n"
				<<endl;
			NUM++;
		}
		return;
	}
};

Quadrangle * newQuadrangle (qPtr p) {
	double input;
	char key;

		//提供关键字
		p->draw();
		//用户输入答案
		cout<<"please input your answer:"
			<<endl;
		while(true){
			cin>>input;
			//检查答案并给出结果
			if (input == p->area()){
				cout<<"Bingo!\n"
					<<endl;
				break;
			}
			else {
				cout<<"Wrong, do you want to continue?\n(y for yes and others for no)"<<endl;
				cin>>key;
				if (key!='y'){
					cout<<"the answer is :"
						<<p->area()
						<<endl;
					return p;
				}
				cout<<"please input your answer:";
			}
		}
		return p;
	}

int main () {
	char key;
	int num = 1;
	List *list = new List;

	srand(unsigned(time(NULL)));

	cout<<"shall we start?"
		<<"\n(y for yes and others for exist)"
		<<endl;
	cin>>key;
	if (key != 'y'&&key != 'Y'){
		return false;
	}
	
	key = '1';

	//进入教学程序
	while(true){
		//为图形申请空间
		//注：不可用 Parallelogram pa; 这样的声明，否则会被解析
		qPtr q ;
		Node * nodePtr = new Node;
		Parallelogram * paPtr = new Parallelogram;
		Rect * rPtr = new Rect;
		Diamond * dPtr = new Diamond;
		Square * sPtr = new Square;
		Trapezoid * tPtr = new Trapezoid;

		//声明循环中改变并析构的变量
		int random = 1+rand()%5;
		double width = 1+rand()%10;
		double height = 1+rand()%10;

		if (key == '1'){
			//选择四边形
			if (random==1){
				Parallelogram p(width,height);
				*paPtr = p;
				q=paPtr;
			}
			else if (random==2){
				Rect p(width,height);
				*rPtr = p;
				q=rPtr;
			}
			else if (random==3){
				double a=width;
				double b=height;
				Diamond p(a,b);
				*dPtr = p;
				q=dPtr;
			}
			else if (random==4){
				double a=width;
				Square p(a);
				*sPtr = p;
				q = sPtr;
			}
			else {
				double a=width;
				double b=rand()%10;
				Trapezoid p(a,b,height);
				*tPtr = p;
				q=tPtr;
			}
		}

		switch(key){
		case '1':
			//测试程序开始
			newQuadrangle(q);
			list->pushBack(q,nodePtr);
			break;
		case '2':
			//review
			list->walkList();
			break;
		case '3':
			cout<<"\n\n\nBye~"
				<<endl;
			system("pause");
			return false;
		default:
			cout<<"\nERROR!!!please try again!\n\n"
				<<endl;
			break;
		}
		num++;

		cout<<"please pick your choice:"
			<<"\n\t1 go on;"
			<<"\n\t2 review;"
			<<"\n\t3 exit;"
			<<endl;

		cin>>key;
	}
}