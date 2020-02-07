#ifndef CONJCADENA_H
#define CONJCADENA_H
#include <iostream>

namespace tads{

	class Conjunto{
		public:
			Conjunto();
			Conjunto(const Conjunto &o);
			~Conjunto();
			void incluirplb(const std::string &plb);
			void incluirconj(const Conjunto &o);
			bool contiene(const std::string &plb)const;
			void borrar(const std::string &plb);
			void vaciar();
			Conjunto &operator=(const Conjunto &o);
			std::string cadena()const;
			void sig();
			bool vacia();

		private:
			struct TNodo{
				std::string cadena;
				TNodo* sig;
			};

			typedef TNodo* TLista;

			TLista l;

			TLista duplicar(TLista li)const;
	};
}

#endif
