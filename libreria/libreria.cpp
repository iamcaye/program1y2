#include "libreria.hpp"

namespace tads{

	Libreria::~Libreria(){
		borrarTodos();
	}

	Libreria::Libreria(): l(NULL), autores(0){}

	Libreria::Libreria(const Libreria &o): autores(o.autores){
		l = duplicar(o.l);
	}

	void Libreria::mostrar()const{
		TLista tmp;

		std::cout << "[" << autores.size() << "] {" ;

		for(int k = 0 ; k < autores.size() ; k++){
			std::cout << autores[k];

			if(k < autores.size()-1){
				std::cout << ", ";
			}
		}
		std::cout << "}" << std::endl;

		tmp = l;

		std::cout << "{" << endl;

		while(tmp != NULL){
			tmp -> libro.mostrar();
			if(tmp -> sig != NULL){
				std::cout << ", ";
			}
		}

		std::cout << "}" << std::endl;
	}

	int Libreria::consultar_num_libros()const{
		int cont = 0;
		TLista tmp = l;

		while(tmp != NULL){
			cont++;
			tmp = tmp -> sig;
		}

		return cont;
	}

	void Libreria::anadir_libro(const std::string &autor, const std::string &tit){
		TLista tmp = l;

		while((tmp != NULL) && (tmp -> libro.consultar_autor() != autor) || tmp -> (libro.consultar_titulo() != tit)){
			tmp = tmp -> sig;
		}
		
		if(tmp != NULL){
			tmp -> libro = li;
		}else{
			tmp = new TNodo;
			tmp -> libro = li;
			tmp -> sig = NULL;
		}
		 
	}

	double Libreria::consultar_precio(const std::string &autor, const std::string &tit)const{
		TLista tmp;
		double precio = -1;
		tmp = l;

		while((tmp != NULL)&&(tmp -> libro.consultar_autor() != autor) || tmp -> (libro.consultar_titulo() != tit)){
			tmp = tmp -> sig;
		}

		if(tmp != NULL){
			precio = tmp -> libro.consultar_precio();
		}

		return precio;
	}

	double Libreria::consultar_preciofinal(const std::string &autor, const std::string &tit)const{
		double precio = consultar_precio();
		int pos=0;

		if(precio != -1){
			while((pos < autores.size()) && (autores[pos] != autor)){
				pos++;
			}

			if(pos < actore.size()){
				precio = precio/2;
			}
		}

		return precio;
	}

	void Libreria::eliminar_libros_oferta(){
		TLista tmp, ant;
		int pos;

		ant = NULL;
		tmp = l;

		while(tmp != NULL){
			pos = 0;

			while((pos < autores.size()) && (autores[pos] != tmp -> libro.consultar())){
				pos++
			}

			if(pos < autores.size()){
				if(ant != NULL){
					ant -> sig = tmp -> sig;
					delete tmp
					tmp = ant -> sig;
				}else{
					l = tmp -> sig;
					delete tmp;
					tmp = l;
				}
			}else{			
				ant = tmp;
				tmp = tmp -> sig;
			}
		}
	}


}
