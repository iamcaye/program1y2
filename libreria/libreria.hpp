#ifndef LIBRERIA_H
#define LIBRERIA_H

#include <vector>
#include <iostream>

namespace tads{

	class Libreria{
		public:
			~Libreria();

		private:
			struct Libro{
				std::string autor, titulo;
				double precio;
			};

			struct TNodo{
				Libro Libro;
				TNodo* sig;
			};

			typedef TNodo* TLista;
			TLista l;

			typedef vector <string> TAnt;
			TAnt autores;

	};

}

#endif
