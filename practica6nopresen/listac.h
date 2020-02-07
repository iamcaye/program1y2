#ifndef LISTAC_H
#define LISTA_H

#include <iostream>
#include "conjunto.h"

namespace tads{

	class ListaC{
		public:
			ListaC();
			ListaC(const ListaC &o);
			~ListaC();
			ListaC &operator=(const ListaC &o);
			void almacenar(unsigned pos, const Conjunto &v);
			void insertar(unsigned pos, const Conjunto &v);
			void borrar(int pos);
			void borrarTodo();
			Conjunto obtener(int pos);
			Conjunto valores()const;
			float soporte(const Conjunto &v)const;


		private:
			struct TNodo{
				Conjunto datos;
				TNodo* sig;
			};

			typedef TNodo* TListaC;
			TListaC p;
			int ne;

			TListaC duplicar(TListaC li)const;
	};

}

#endif
