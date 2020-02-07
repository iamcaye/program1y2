//Cayetano Biehler Pollaci
#ifndef MATRIZ_H
#define MATRIZ_H

#include <string>

namespace prEvaluable{

	class MatrizBidimensional{

		public:

			MatrizBidimensional();
			void definirAlto(int num);
			void definirAncho(int num);
			void almacenar(int x, int y, int valor);
			double obtener(int x, int y)const;
			int ancho()const;
			int alto()const;
			void mostrar()const;
			void leerDeFichero(const std::string &nom);
			void escribirAFichero(const std::string &nom)const;

		private:
		
			static const int max = 10;
			typedef int Columnas[max];
			typedef Columnas TMatriz[max];
			TMatriz matriz;
			int anch, alt;

	};

}

#endif
