#pragma once
#include "List.h"
#include "stdafx.h"

	void List::pushBack(qPtr Quad ,Node * node){
		Node *newNode = node;
		newNode->next=NULL;

		this->tail->quad = Quad;
		this->tail->next = newNode;
		this->tail=this->tail->next;
		this->num++;
		return;
	}

	int List::size () {return num;}
	void List::pop_back() {
		Node *p =this->head;
		int NUM = 1;
		
		for (;NUM<=num-1;p=p->next){
			NUM++;
		}
		delete(p);
		num--;
		return;
	}
	void List::traverse (){
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
	List & List::operator += (qPtr Quad) {
		Node * node = new Node; 
		this->pushBack(Quad,node);
		return *this;
	}
	List & List::operator = (List & l) {
		int n = l.num;
		Node *node = l.head;
		for (int i = 1;i<=n;i++){
			*this+=(node->quad);
			n++;
		}
		return *this;
	}
	QUADPTR & List::operator [] (int index) {
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