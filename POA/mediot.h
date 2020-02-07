#ifndef MEDIOT_H
#define MEDIOT_H

namespace viaje{

	class MedioT{
		public:
			MedioT();
			~MedioT();
			MedioT(double epk);
			double coste(double km)const;

		private:
			double eurospk;
	};
}

#endif
