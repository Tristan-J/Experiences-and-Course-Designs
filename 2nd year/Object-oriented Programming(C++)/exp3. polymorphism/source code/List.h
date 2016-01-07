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
	void pushBack(qPtr Quad ,Node * node);
public:
	Node *head,*tail ;
	int num;
	List(){
		num = 0;
		head=new Node;
		tail=head;
		tail->next=NULL;
	}
	~List() {}
	int size ();
	void pop_back();
	void traverse ();
	List & operator += (qPtr Quad) ;
	List & operator = (List & l) ;
	QUADPTR & operator [] (int index) ;
};