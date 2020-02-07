#ifndef PUNTO_HPP
#define PUNTO_HPP

namespace gps{

	class Punto{
		public:
			~Punto();
			Punto();
			Punto(const Punto &o);
			Punto(double cx, double cy);
			void mostrar()const;
			void desplazar(double dx, double dy);
			double distancia(const Punto &p)const;
			double dx()const;
			double dy()const;
			

		private:
			double x,y;
	};
}

#endif
