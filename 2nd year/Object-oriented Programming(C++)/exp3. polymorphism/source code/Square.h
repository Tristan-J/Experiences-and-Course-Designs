#pragma once
#include <iostream>
#include <string.h>
#include <string>
#include <time.h>
using std::string;
using namespace std;

//(1)	在quad.h（或类似）插入如下一行：
#include "Canvas.h"
#include "Rectangle.h"


//Square
class Square :public Rect {
private:
	string name;
	double width;
	double height;
public:
	Square (double iA=2.0):name("Square"),width(iA),height(iA){}
	~Square () {}
	double area();
	void draw();
	double Width();
	double Height();
	string what();
	void operator = (Square * quad);
	friend int operator > (Square & s1, Square & s2);
	friend ostream& operator << (ostream& os,Square & s);
};