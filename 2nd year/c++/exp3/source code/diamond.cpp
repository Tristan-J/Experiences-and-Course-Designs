#pragma once
#include "Diamond.h"
#include "stdafx.h"

	double Diamond::area(){
		return   width*height;
	}
	void Diamond::draw(){
		Canvas::drawQuad(this);
		return;
	}
	double Diamond::Width() {return width;}
	double Diamond::Height() {return height;}
	string Diamond::what(){return name;}
	void Diamond::operator = (Diamond * quad) {
		width = quad->Width();
		height = quad->Height();
		return;
	}
	int operator > (Diamond & d1, Diamond & d2) {
		return d1.area()>d2.area();
	}
	ostream& operator << (ostream& os,Diamond & d) {
		d.draw();
		return os;
	}