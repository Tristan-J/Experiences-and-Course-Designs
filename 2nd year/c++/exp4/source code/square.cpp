#pragma once
#include "Square.h"
#include "stdafx.h"

	double Square::area(){
		return width*height;
	}
	void Square::draw(){
		Canvas::drawQuad(this);
		return;
	}
	double Square::Width() {return width;}
	double Square::Height() {return height;}
	string Square::what(){return name;}
	void Square::operator = (Square * quad) {
		width = quad->Width();
		return;
	}
	int operator > (Square & s1, Square & s2) {
		return s1.area()>s2.area();
	}
	ostream& operator << (ostream& os,Square & s) {
		s.draw();
		return os;
	}