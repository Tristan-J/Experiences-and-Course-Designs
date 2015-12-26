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

//the child classes
//Trapezoid
class Trapezoid:public Quadrangle{
private:
	string name;
	double width,width2,height;
public:
	Trapezoid (double iA=1.0,double iB=2.0,double iH=2.0):name("Trapezoid"),width(iA),width2(iB),height(iH){}
	double area();
	void draw();
	double Width() ;
	double Width2() ;
	double Height() ;
	string what();
	void operator = (Trapezoid * quad);
	friend int operator > (Trapezoid & t1, Trapezoid & t2);
	friend ostream& operator << (ostream& os,Trapezoid & t) ;
};