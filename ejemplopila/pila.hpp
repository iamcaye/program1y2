
#ifndef PILA_H
#define PILA_H

#include <iostream>
#include <cstdlib>

namespace mPila{

	template <typename TBase, int max>
	class Pila{
	public:
		void pila(){
			ne = 0;
		}

		void apilar(const TBase &v){

			if(ne==max){
				std::cout << "Pila llena" << std::endl;
				std::exit(1);
			}else{
				datos[ne] = v;
				ne++;
			}

		}

		TBase desapilar(){

			if(ne == 0){
				std:: cout << "Pila vacia" << std::endl;
				std::exit(1);
			}else{
				ne--;
			}
			return datos[ne];
		}

		int tamanio()const{
			return ne;
		}

	private:
		typedef TBase TLista[max];

		int ne;
		TLista datos;
	};
}

#endif


