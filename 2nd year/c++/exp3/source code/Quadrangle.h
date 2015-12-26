#pragma once
#include <iostream>
#include <string.h>
#include <string>
#include <time.h>
using std::string;
using namespace std;

//(1)	在quad.h（或类似）插入如下一行：
#include "Canvas.h"
#include "List.h"

//Quadrangle
class Quadrangle {
public:
	string name;
	virtual double area()=0;
	virtual void draw()=0;
	virtual string what()=0;
};
typedef Quadrangle *qPtr;
typedef Quadrangle *QUADPTR;