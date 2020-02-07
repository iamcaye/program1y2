#ifndef PILA_H
#define PILA_H

#include "conjunto.h"

namespace tads{

	class Pila{
		public:
			Pila();
			Pila(const Pila &o);
			~Pila();
			Pila &operator=(const Pila &o);
			void apilar(const Conjunto &v);
			Conjunto desapilar();
			bool vacia();
			void borrarTodo();

		private:
			struct TNodo{
				Conjunto datos;
				TNodo* sig;
			};

			typedef TNodo* TListaC;
			TListaC p;

			TListaC duplicar(TListaC li)const;
			
	};

}

#endif
