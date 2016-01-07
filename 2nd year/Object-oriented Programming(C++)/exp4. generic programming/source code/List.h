#pragma once
#include <iostream>
#include <string.h>
#include <string>
#include <time.h>
using std::string;
using namespace std;

//(1)	在quad.h（或类似）插入如下一行：
#include "Canvas.h"
#include "Quadrangle.h"
#include "Parallelogram.h"
#include "Rectangle.h"
#include "Diamond.h"
#include "Trapezoid.h"
#include "Square.h"

//list
template <typename T>
class List {
public: 

	friend class Node ;
	class Node {
	public:
		T quad; //pro: qPtr
		Node *next;
		Node(){}
		~Node(){}
	};

	friend class Iterator;
	class Iterator {
	private :

	public:
		List <T> * plist;
		typename List <T> ::Node *p;

		Iterator (const List <T> & list ) :plist(const_cast <List <T> * > (&list)),p(list.head){}
		Iterator ( Iterator & itr ) :plist( itr.plist) , p(itr.p){}
		Iterator () : plist(NULL) , p(NULL) {}
		
		Iterator & begin() {
			return *this;
		}
		Iterator end () {
			return Iterator();
		}

		Iterator & operator = (const Iterator & itr ) {
			plist = itr.plist;
			p = itr.p;
			return *this;
		}
		Iterator & operator ++ () {
			p = p->next;
			return *this;
		}
		bool operator != (const Iterator & itr) {
			return p != itr.p;
		}
		T & operator * () {
			return p->quad;
		}
		Iterator operator + (int i) {
			Iterator temp = *this;
			for (int j =0;j != i;j++){++temp;}
			return temp;
		}
	};

protected:
	void pushBack(T Quad ,Node * node) {
		Node *newNode = node;
		newNode->next=NULL;

		this->tail->quad = Quad;
		this->tail->next = newNode;
		this->tail=this->tail->next;
		this->num++;
		return;
	}
public:
	Node *head,*tail ;
	int num;
	Iterator *lItr;
	List(){
		num = 0;
		head=new Node;
		tail=head;
		tail->next=NULL;
		lItr = new Iterator;
		lItr->p = head;
	}
	~List() {}
	int size (){return num;}
	void pop_back(){
		Node *p =this->head;
		int NUM = 1;
		
		for (;NUM<=num-1;p=p->next){
			NUM++;
		}
		delete(p);
		num--;
		return;
	}
	void traverse () {
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
	List & operator += (T Quad) {
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
	QUADPTR & operator [] (int index) {
		Node *node = this->head;
		if (index<0){
			throw int (index) ;
		}
		else if (this->num<=index){
			throw long (index);
		} 
		else {
			for (int i =0 ;i<index;i++) {
				node = node->next;
			}
		}
		return node->quad;
	}
	Iterator begin () {
		lItr->p = head;
		return lItr->begin() ;
	}
	Iterator end () {
		lItr->p = head;
		return lItr->end();
	}
};