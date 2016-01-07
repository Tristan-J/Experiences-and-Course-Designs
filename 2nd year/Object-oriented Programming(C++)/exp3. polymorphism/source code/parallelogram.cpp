#pragma once
#include "Parallelogram.h"
#include "stdafx.h"

	double Parallelogram::area(){
		return  width*height;
	}
	void Parallelogram::draw(){
		Canvas::drawQuad(this);
		return;
	}
	double Parallelogram::Width() {return width;}
	double Parallelogram::Height() {return height;}
	string Parallelogram::what(){return name;}
	void Parallelogram::operator = (Parallelogram * quad) {
		width = quad->Width();
		height = quad->Height();
		return;
	}
	int operator > (Parallelogram & p1, Parallelogram & p2) {
		return p1.area()>p2.area();
	}
	ostream& operator << (ostream& os,Parallelogram & p) {
		p.draw();
		return os;
	}