#pragma once
#include "Rectangle.h"
#include "stdafx.h"

	double Rect::area(){
		return width*height;
	}
	void Rect::draw(){
		Canvas::drawQuad(this);
		return;
	}
	double Rect::Width() {return width;}
	double Rect::Height() {return height;}
	string Rect::what(){return name;}
	void Rect::operator = (Rect * quad) {
		width = quad->Width();
		height = quad->Height();
		return;
	}
	int operator > (Rect & r1, Rect & r2) {
		return r1.area()>r2.area();
	}
	ostream& operator << (ostream& os,Rect & r) {
		r.draw();
		return os;
	}