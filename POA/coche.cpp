#include "coche.h"

namespace viaje{
	coche::coche():MedioT(){}
	coche::~coche(){}
	coche::coche(double epk):MedioT(epk){}
	double coche::coste(double km)const{
		return MedioT::coste(km) + km*euroskpeaje;
	}
}
