#include "conjunto.h"

#include <iostream>

namespace tads{
	Conjunto::Conjunto():l(NULL){}

	Conjunto::Conjunto(const Conjunto &o){
		l = duplicar(o.l);
	}

	Conjunto::~Conjunto(){
		vaciar();
	}

	Conjunto &Conjunto::operator=(const Conjunto &o){

		if(this != &o){
			vaciar();
			l = duplicar(o.l);
		}

		return *this; 
	}

	void Conjunto::incluirplb(const std::string &plb){
		TLista tmp = l,ant = NULL;

		/*if(tmp == NULL){

			tmp = new TNodo;
			tmp -> cadena = plb;
			tmp -> sig = NULL;
			l = tmp;

		}else{

			while((tmp != NULL)&&(plb != l -> cadena)){
				ant = tmp;
				tmp = tmp -> sig;
			}

			if(tmp == NULL){
				tmp = new TNodo;
				tmp -> cadena = plb;
				tmp -> sig = NULL;
				ant -> sig = tmp;
			}
		}*/

		
		while((tmp != NULL)&&(plb != l -> cadena)){
			ant = tmp;
			tmp = tmp -> sig;
		}

		if(ant == NULL){
			tmp = new TNodo;
			tmp -> cadena = plb;
			tmp -> sig = NULL;
			l = tmp;			
		}else{
			tmp = new TNodo;
			tmp -> cadena = plb;
			tmp -> sig = NULL;
			ant -> sig = tmp;
		}
		
	}

	void Conjunto::incluirconj(const Conjunto &o){
		TLista tmp = o.l;

		while(tmp != NULL){
			tmp = tmp -> sig;
		}

		tmp = l;
	}

	bool Conjunto::contiene(const std::string &plb)const{
		bool esta = false;
		TLista tmp = l;

		while((tmp != NULL)&&(plb != l -> cadena)){
			tmp = tmp -> sig;
		}

		if(tmp != NULL){
			esta = true;
		}

		return esta;
	}

	void Conjunto::borrar(const std::string &plb){
		TLista tmp,ant;
		tmp = l;
		ant = NULL;

		while(tmp != NULL && plb != tmp -> cadena){
			ant = tmp;
			tmp = tmp -> sig; 
		}

		if(tmp == NULL){
			std::cout << "Error borrarplb" << std::endl;
		}else{
			if(ant == NULL){
				l = l -> sig;
			}else{
				ant -> sig = tmp -> sig;
			}
			delete tmp;
		}

		
	}

	void Conjunto::vaciar(){
		TLista tmp;

		while(tmp != NULL){
			tmp = l;
			l = l -> sig;
			delete tmp;
		}
	}

	Conjunto::TLista Conjunto::duplicar(TLista li)const{

		TLista res, rec, ult, nue;

		rec = li;
		res = NULL;
		ult = NULL;

		while(rec != NULL){

			nue = new TNodo;
			nue -> cadena = rec -> cadena;
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

	std::string Conjunto::cadena()const{
		return l -> cadena;
	}

	void Conjunto::sig(){
		l = l -> sig;
	}

	bool Conjunto::vacia(){
		return l == NULL;
	}

	
}
