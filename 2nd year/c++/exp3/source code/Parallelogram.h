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

//Parallelogram
class Parallelogram :public Quadrangle{
private:
	string name;
	double width,height;
public:
	Parallelogram (double iA=2.0,double iH=1.0):name("Parallelogram"),width(iA),height(iH){}
	~Parallelogram () {}
	double area();
	void draw();
	virtual double Width();
	virtual double Height();
	string what();
	void operator = (Parallelogram * quad) ;
	friend int operator > (Parallelogram & p1, Parallelogram & p2) ;
	friend ostream& operator << (ostream& os,Parallelogram & p) ;
};