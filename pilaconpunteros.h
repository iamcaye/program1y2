#ifndef PILACONPUNTEROS_H
#define PILACONPUNTEROS_H

	#include <cstdlib>
	#include <iostream>

	using namespace std;

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
				
				l = duplicar(o.l)
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

					cout << "ERROR 1" << endl;
					exit(1);

				}

				return res;

			}

			bool vacia(){

				return l==NULL;

			}


			Pila<TBase>& operator=(const Pila<TBase> &o){		//eliminar todos los nodos de "l" y duplicar o.l

				if(this != &o){
					borrarTodo(l);
					l = duplicar(o.l);
				}

				return *this; 
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

#endif
