#pragma once
#include "Trapezoid.h"
#include "stdafx.h"

	void Trapezoid:: draw(){
		Canvas::drawQuad(this);
		return;
	}
	double Trapezoid::Width() {return width;}
	double Trapezoid::Width2() {return width2;}
	double Trapezoid::Height() {return height;}
	string Trapezoid::what(){return name;}
	void Trapezoid::operator = (Trapezoid * quad) {
		width = quad->Width();
		width2 = quad->Width2();
		height = quad->Height();
		return;
	}
	double Trapezoid::area(){
		return (width+width2)*height*0.5;
	};
	int operator > (Trapezoid & t1, Trapezoid & t2) {
		return t1.area()>t2.area();
	}
	ostream& operator << (ostream& os,Trapezoid & t) {
		t.draw();
		return os;
	}