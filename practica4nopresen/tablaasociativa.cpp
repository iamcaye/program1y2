#include "tablaasociativa.h"

#include <iostream>
#include <fstream>

namespace tads{

	TablaAsociativa::TablaAsociativa(){

		for(unsigned k = 0 ; k < TAM ; k++){
			tabla[k] = NULL;
		}

	}
	
	TablaAsociativa::~TablaAsociativa(){
		for(int k = 0 ; k < TAM ; k++){
			borrarTodos(k)
		}
	}
	
	TablaAsociativa::TablaAsociativa(const TablaAsociativa &o){
		for (int k = 0 ; k < TAM ; k++){
			tabla[k] = duplicar(o.tabla[k])
		}
	}
	
	unsigned TablaAsociativa::fHash(const std::string &c){
		unsigned suma;
		suma = 0;
		
		for( unsigned k = 0; k < c.size(); k++ ){
			suma = suma + unsigned( c[k] );
		}
		
		suma = suma % TAM;
		return suma;
	}
	
	TablaAsociativa::TLista TablaAsociativa::duplicar(const TablaAsociativa &o){
		TLista rec, res, ult, nue;
		rec = l;
		res = NULL;
		ult = NULL;
		
		while(rec != NULL){
			nue = new TNodo;
			nue -> clave = rec -> clave;
			nue -> valor = rec -> valor;
			nue -> sig = NULL;
			
			if(res == NULL){
				res = nue;
			}else{
				ult -> sig = nue;
			}
			
			ult = nue;
			rec = rec -> sig;
		}
		return res;
	}
	
	bool TablaAsociativa::existe(const std::string &cl)const{
		TLista tmp;
		int pos = fHash(cl)
		tmp = tabla[pos]
		

		while((tmp != NULL) && tmp -> clave != cl){
			tmp = tmp -> sig;
		}
				
		return tmp != NULL;
	}
	
	void TablaAsociativa::incluir(const std::string &cl, const std::string &va){
		int pos = fHash(cl);
		TLista tmp, aux;
		
		aux = tabla[pos];
		
		while((aux != NULL) && aux -> clave != cl){
			aux = aux -> sig;
		}
		if(tmp == NULL){
			tmp = new TNodo;
			tmp -> clave = cl;
			tmp -> valor = va;
			tmp -> sig = tabla[k];
			tabla[k] = tmp;
			
		}else{
			tmp -> valor = va;
		}
			
	}
	
	std::string TablaAsociativa::obtener(const std::string &cl)const{
		int pos = fHash(cl);
		std::string p;
		TLista aux;
		
		aux = tabla[pos];
		
		while((aux != NULL) && aux -> clave != cl){
			aux = aux -> sig;
		}
		
		if(aux == NULL){
		
			std::cout << "Error obtener" << std::endl;
			
		}else if(aux -> cl == cl){
		
			p = aux -> valor;
		}
		return p;
	}
	
	void TablaAsociativa::borrar(const std::string &cl){
		int pos = fHash(cl);
		TLista tmp, aux, ant;
		
		ant = NULL;
		tmp = NULL;
		aux = tabla[pos];
		
		while((aux != NULL) && aux -> clave != cl){
			ant = aux;
			aux = aux -> sig;
		}
		
		if(aux != NULL){
			tmp = aux -> sig;
			ant -> sig = tmp;
			delete aux;
			
		}
	}
	
	void TablaAsociativa::grabar(const std::string &f){
		TLista tmp;
		
		std::ofstream FSal;
		
		std::FSal.open(f.c_str());
		
		if(f.good()){
			for(int k = 0 ; k < TAM ; k++){
				if(tabla[k] != NULL){
					tmp = tabla[k]
					while(tmp != NULL){
						std::FSal >> tmp -> clave << '\t' << tmp -> valor << std::endl;
						tmp = tmp -> sig;
					}
				}
			}
		}
		
		FSal.close();
	}
	
	/*void TablaAsociativa::cargar(const std::string &f){
		TLista tmp;
		
		std::ifstream FEnt;
		
		std::FEnt.open(f.c_str());
		
		while(!FEnt.eof())
		
		FSal.close();
	}*/
}
