#include "punto.hpp"

#include <iostream>
#include <cmath>

namespace gps{

	Punto::Punto():x(0),y(0){}

	//Punto::~Punto():x(),y(){}

	Punto::Punto(const Punto &o){
		x = o.dx();
		y = o.dy();
	}

	Punto::Punto(double cx, double cy):x(cx),y(cy){}

	void Punto::mostrar()const{
		std::cout << "(" << x << ", " << y << ")" << std::endl;
	}

	void Punto::desplazar(double dx, double dy){
		x = x+dx;
		y = y+dy;
	}

	double Punto::distancia(const Punto &p)const{
		return sqrt(pow((x - p.dx()),2) + pow((y - p.dy()),2));
	}

	double Punto::dx()const{
		return x;
	}

	double Punto::dy()const{
		return y;
	}

}
