#ifndef PALETA_H
#define PALETA_H

namespace jTenis{

	class Paleta{
		public:
			Paleta();
			void defPos(int col, int fil);
			void mover();
			void arriba();
			void abajo();
			bool toca(int col, int fil)const;
	
		private:
			static const int VEL = 50000;
			static const char DIB = '#';
			static const int TAM = 2 ;
			int x;
			int y;//Fila central en pantalla de la paleta. 
			int dy;//Direccion del movimiento(vector velocidad)
			void dibujar(char c)const;
			int ymin, ymax, paso;

			

	};
}

#endif
