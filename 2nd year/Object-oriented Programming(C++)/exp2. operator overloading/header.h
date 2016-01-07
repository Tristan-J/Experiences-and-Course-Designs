#include <iostream>
#include <string>
#include <time.h>
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
	void draw();
	double getWidth() {return a;}
	double getWidth2() {return b;}
	double getHeight() {return height;}
	void operator = (Trapezoid * quad) {
		a = quad->getWidth();
		b = quad->getWidth2();
		height = quad->getHeight();
		return;
	}
	friend int operator > (Trapezoid & t1, Trapezoid & t2) {
		return t1.area()>t2.area();
	}
	friend ostream& operator << (ostream& os,Trapezoid & t) {
		t.draw();
		return os;
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
	double getWidth() {return width;}
	double getHeight() {return height;}
	void operator = (Parallelogram * quad) {
		width = quad->getWidth();
		height = quad->getHeight();
		return;
	}
	friend int operator > (Parallelogram & p1, Parallelogram & p2) {
		return p1.area()>p2.area();
	}
	friend ostream& operator << (ostream& os,Parallelogram & p) {
		p.draw();
		return os;
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
	double getWidth() {return width;}
	double getHeight() {return height;}
	void operator = (Rect * quad) {
		width = quad->getWidth();
		height = quad->getHeight();
		return;
	}
	friend int operator > (Rect & r1, Rect & r2) {
		return r1.area()>r2.area();
	}
	friend ostream& operator << (ostream& os,Rect & r) {
		r.draw();
		return os;
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
	double getWidth() {return width;}
	double getHeight() {return height;}
	void operator = (Diamond * quad) {
		width = quad->getWidth();
		height = quad->getHeight();
		return;
	}
	friend int operator > (Diamond & d1, Diamond & d2) {
		return d1.area()>d2.area();
	}
	friend ostream& operator << (ostream& os,Diamond & d) {
		d.draw();
		return os;
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
	double getWidth() {return a;}
	void operator = (Square * quad) {
		a = quad->getWidth();
		return;
	}
	friend int operator > (Square & s1, Square & s2) {
		return s1.area()>s2.area();
	}
	friend ostream& operator << (ostream& os,Square & s) {
		s.draw();
		return os;
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
	void pushBack(qPtr Quad ,Node * node){
		Node *newNode = node;
		newNode->next=NULL;

		this->tail->quad = Quad;
		this->tail->next = newNode;
		this->tail=this->tail->next;
		this->num++;
		return;
	}
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
	List & operator += (qPtr Quad) {
		Node * node = new Node; 
		this->pushBack(Quad,node);
		return *this;
	}
	List & operator = (List & l) {
		int n = l.num;
		Node *node = l.head;
		for (int i = 1;i<=n;i++){
			*this+=(node->quad);
			n++;
		}
		return *this;
	}
	List & operator [] (int index) throw (int,long) {
		if (index<0){
			throw int (index) ;
		}
		else if (this->num<=index){
			throw long (index);
		}
		else {
			Node *node = this->head;
			for (int i =0 ;i<index;i++) {
				node = node->next;
			}
			node->quad->draw();
			cout<<"the area is:"
				<<node->quad->area()
				<<"\n"
				<<endl;
		}
		return *this;
	}
};