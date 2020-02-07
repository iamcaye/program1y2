#include "listac.h"
#include <fstream>

namespace tads{

	ListaC::ListaC():ne(),p(){}

	ListaC::ListaC(const ListaC &o){
		p = duplicar(o.p);
	}

	ListaC::~ListaC(){
		p -> datos.vaciar();
		ne = 0;
	}

	ListaC &ListaC::operator=(const ListaC &o){

		if(this != &o){
			borrarTodo();
			p = duplicar(o.p);
		}

		return *this; 

	}

	ListaC::TListaC ListaC::duplicar(TListaC li)const{

			TListaC res, rec, ult, nue;

			rec = li;
			res = NULL;
			ult = NULL;

			while(rec != NULL){

				nue = new TNodo;
				nue -> datos = rec -> datos;
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

	void ListaC::almacenar(unsigned pos, const Conjunto &v){

		TListaC tmp;
		tmp = p;

		while((tmp != NULL)&&(pos > 0)){
			pos--;
			tmp = tmp -> sig;
		}	

		if(tmp == NULL){
			std::cout << "Error de almacenar" << std::endl;
		}else{	
			tmp -> datos = v;
		}
	}

	void ListaC::insertar(unsigned pos, const Conjunto &v){

		TListaC tmp, ant, nue;

		tmp = p;
		ant = NULL;

		while((tmp != NULL)&&(pos > 0)){
			pos--;
			ant = tmp;
			tmp = tmp -> sig;
		}

		nue = new TNodo;
		nue -> datos = v;
		nue -> sig = tmp;
		if(tmp == NULL){
			p = nue;
		}else{
			
			ant -> sig = nue;
		}

		ne++;

	}

	void ListaC::borrar(int pos){

		TListaC tmp, ant;
		tmp = p;
		ant = NULL;

		while((tmp != NULL)&&(pos > 0)){
			pos--;
			ant = tmp;
			tmp = tmp -> sig;
		}//while

		if(tmp == NULL){
			std::cout << "Error borrarpos" << std::endl;			
		}else{
			if(ant == NULL){
				p = p-> sig;
			}else{
				ant -> sig = tmp -> sig;
			}
			delete tmp;
			ne--;
		}

	}

	void ListaC::borrarTodo(){
		for(int k = 0 ; k < ne ; k++){
			borrar(k);
		}
	}

	Conjunto ListaC::obtener(int pos){

		TListaC tmp;
		tmp = p;

		while((tmp != NULL)&&(pos > 0)){
			pos--;
			tmp = tmp -> sig;
		}	

		if(tmp == NULL){
			std::cout << "Error de obtener" << std::endl;
		}	
		return tmp -> datos;

	}

	Conjunto ListaC::valores()const{

		TListaC tmp = p;
		Conjunto c;
		int k = 0;
		if(ne != 0){

			for( k = 0 ; k < ne ; k++){
				c.incluirconj(tmp -> datos);
				tmp = tmp -> sig;
			}
		}
		return c;
	}

	float ListaC::soporte(const Conjunto &v)const{

		int cont;		
 		bool ok = true;
		Conjunto copia;
		TListaC tmp = p;

		while(tmp != NULL){
			copia = v;
			ok = true;
			while((!copia.vacia())&&ok){
				if(!tmp -> datos.contiene(copia.cadena())){
					ok = false;
				}
				copia.sig();
			}
			if(ok){
				cont++;
			}
			tmp = tmp -> sig;
		}
		
		return (cont/ne)*100;
	}

	


}
