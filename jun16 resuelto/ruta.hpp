#ifndef RUTA_HPP
#define RUTA_HPP

#include "punto.hpp"
#include <iostream>

namespace gps{

	class Ruta{
		public:
			Ruta();
			~Ruta();
			Ruta(const Ruta &o);
			void mostrar()const;
			void anadirPunto(const Punto &pto);
			void desplazar(double dx, double dy, double maxx, double maxy, double minx, double miny);
			double distanciaTotal()const;
			bool esInverso(const Ruta &rut)const;
			int npuntos()const;
			Punto buscarPto(int pos)const;
			void eliminarCamino(const Punto &pto);

		private:
			struct TNodo{
				Punto p;
				TNodo* sig;
			};

			typedef TNodo* TLista;

			TLista l;
			int ne;

			void duplicar(const Ruta &rut){
				int i = 0;
				while(i < rut.npuntos()){
					anadirPunto(buscarPto(i));
				}
			}

			void borrarTodo(){
				TLista tmp = l;

				while(tmp != NULL){
					tmp = l;
					l = l -> sig;
					delete tmp;
				}		
			}

	};

}

#endif


