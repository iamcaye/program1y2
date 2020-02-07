#include "pila.h"


namespace tads{

	Pila::Pila():p(){}

	Pila::Pila(const Pila &o){
		p = duplicar(o.p);
	}

	Pila::~Pila(){
		p -> datos.vaciar();
	}

	Pila &Pila::operator=(const Pila &o){

		if(this != &o){
			borrarTodo();
			p = duplicar(o.p);
		}

		return *this; 

	}

	bool Pila::vacia(){
		return p == NULL;
	}

	void Pila::apilar(const Conjunto &v){

		TListaC tmp = p;

		while(p != NULL){
			tmp = tmp -> sig;
		}

		tmp = new TNodo;
		tmp -> datos = v;
		
	}

	Conjunto Pila::desapilar(){

		TListaC tmp, ant;
		
		if(p!=NULL){

			tmp = p;
			ant = NULL;
			while(tmp != NULL){
				ant = tmp;
				tmp = tmp -> sig;
			}

			if(ant != NULL){
				ant -> sig = NULL;
			}
	
			return tmp -> datos;
		
		}
	}

	void Pila::borrarTodo(){
		while(p != NULL){
			desapilar();
		}
	}
}
