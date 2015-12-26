#pragma once
#include <iostream>
#include <string.h>
#include <string>
#include <time.h>
using std::string;
using namespace std;

//(1)	在quad.h（或类似）插入如下一行：
#include "Canvas.h"
#include "Parallelogram.h"

//Rect
class Rect :public Parallelogram{
private:
	string name;
	double width,height;
public:
	Rect (double iA=2.0,double iH=1.0):name("Rectangle"),width(iA),height(iH){}
	~Rect () {}
	double area();
	void draw();
	double Width();
	double Height();
	string what();
	void operator = (Rect * quad);
	friend int operator > (Rect & r1, Rect & r2) ;
	friend ostream& operator << (ostream& os,Rect & r) ;
};