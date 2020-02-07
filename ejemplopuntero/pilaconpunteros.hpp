#ifndef PILACONPUNTEROS_H
#define PILACONPUNTEROS_H

	#include <cstdlib>
	#include <iostream>

namespace Pilapunt{
	template <typename TBase>

	class Pila{

		public:

			Pila(){

				l = NULL;

			}

			~Pila(){

				borrarTodo(l);
				
			}

			Pila(const Pila<TBase> &o){
				
				l = duplicar(o.l);
			}

			void apilar(const TBase &v){

				TLista temp;

				temp = new TNodo;

				temp -> dato = v;
				
				temp -> sig = l;
				
				l = temp;

			}

			TBase desapilar(){

				TBase res;

				if(l != NULL){
					TLista temp;
						
					res = l -> dato;	
					
					temp = l;

					l = l -> sig;

					delete temp;
				}else{

					std::cout << "ERROR 1" << std::endl;
					std::exit(1);

				}

				return res;

			}

			bool vacia()const{

				return l==NULL;

			}


			Pila<TBase>& operator=(const Pila<TBase> &o){		//eliminar todos los nodos de "l" y duplicar o.l

				if(this != &o){
					borrarTodo(l);
					l = duplicar(o.l);
				}

				return *this; 
			}

			int longitud()const{

				int cont = 0;
				TLista tmp = 0;

				while(tmp != NULL){

					cont++;
					tmp = tmp -> sig;

				}
				return cont;
			}

			TBase obtener(int pos)const{

				TLista tmp;
				tmp = l;

				while((tmp != NULL)&&(pos > 0)){
					pos--;
					tmp = tmp -> sig;
				}	

				if(tmp == NULL){
					std::cout << "Error de obtener" << std::endl;
					std::exit(1);
				}	
				return tmp -> dato;
			}

			void borrarPos(int pos){
			
				TLista tmp, ant;
				tmp = l;
				ant = NULL;

				while((tmp != NULL)&&(pos > 0)){
					pos--;
					ant = tmp;
					tmp = tmp -> sig;
				}//while

				if(tmp == NULL){
					std::cout << "Error borrarpos" << std::endl;
					std::exit(1);			
				}else{
					if(ant == NULL){
						l = l -> sig;
					}else{
						ant -> sig = tmp -> sig;
					}
					delete tmp;
				}

			}

			void borrarPares(){
				
				int pos = 0;

				while(pos < longitud()){
					if(obtener(pos) % 2 == 0){
						borrarPos(pos);
					}else{
						pos++;
					}
				}
			}


		private:
			struct TNodo{
				TBase dato;
				TNodo* sig;
			};

			typedef TNodo* TLista;
			TLista l;					

			TLista duplicar(TLista li)const{

				TLista res, rec, ult, nue;

				rec = li;
				res = NULL;
				ult = NULL;

				while(rec != NULL){

					nue = new TNodo;
					nue -> dato = rec -> dato;
					nue -> sig = NULL;
				
					if(res == NULL){
						res = nue;
					}else{
						ult -> sig = nue;
					}

					ult = nue;
					rec = rec -> sig;
				}//while
				return res;
			}

			void borrarTodo(TLista &l)const{
				TLista temp;

				while(l != NULL){

					temp = l;

					l = l -> sig;
				
					delete temp;

				}
			}
	};
}

#endif
