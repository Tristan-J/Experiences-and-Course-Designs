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

//Diamond
class Diamond :public Parallelogram{
private:
	string name;
	double width,height;
public:
	Diamond (double iA=2.0,double iH=1.0):name("Diamond"),width(iA),height(iH){}
	~Diamond () {}
	double area();
	void draw();
	double Width();
	double Height();
	string what();
	void operator = (Diamond * quad);
	friend int operator > (Diamond & d1, Diamond & d2);
	friend ostream& operator << (ostream& os,Diamond & d);
};