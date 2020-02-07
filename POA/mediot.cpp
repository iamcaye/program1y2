#include "mediot.h"

namespace viaje{

	MedioT::MedioT():eurospk(0){}
	MedioT:MedioT(){}
	MedioT::MedioT(double epk):eurospk(epk){}
	double MedioT::coste(double km)const{
		return km*eurospk;
	}

}
