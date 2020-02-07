#ifndef PELOTA_H
#define PELOTA_H

#include "paleta.h"

namespace jTenis{

	class Pelota{
		public:
			Pelota();
			//inicia la pelota en el centro de la pantalla
			void defPos(int x, int y, int d);
			//dice si la pelota esta dentro o fuera de la pantalla
			bool fuera()const;
			bool fueraDer()const;
			bool fueraIzq()const;
			//mueve la pelota
			void mover();
			//metodo pa q la pelota rebote cuando toca la paleta
			void rebotar(const Paleta &pI, const Paleta &pD);

		
		private:
			static const char DIB = '0';
			static const int VEL = 40000;
			int xmin, xmax, ymax, ymin;
			int dy, dx;//vector movimiento de la pelota.
			int x, y;
			int paso=0;

	};
}

#endif
