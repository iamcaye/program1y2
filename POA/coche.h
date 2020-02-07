#ifndef COCHE_H
#define COCHE_H

#include "mediot.h"

namespace viaje{

	class coche:public MedioT{	//para expresar que es herencia de MedioT
		public:
			virtual coche();
			virtual ~coche();
			virtual coche(double epk);
			virtual double coste(double k)const;

		private:
			static const double euroskpeaje = 5;
	};

}

#endif
