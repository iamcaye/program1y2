#include "ruta.hpp"


namespace gps{

	Ruta::Ruta():ne(0){}

	Ruta::Ruta(const Ruta &o){
		duplicar(o);
	}

	Ruta::~Ruta(){
		borrarTodo();
	}

	void Ruta::mostrar()const{
		TLista tmp = l;

		std::cout << "[" << ne << "]" ;
	
		while(tmp != NULL){
			tmp -> p.mostrar();
			tmp = tmp -> sig;
		}
	}

	void Ruta::anadirPunto(const Punto &pto){
		
		TLista tmp = l;

		while(tmp != NULL){
			tmp = tmp -> sig;
		}

		tmp = new TNodo;

		tmp -> p = pto;
		tmp -> sig = NULL;
		ne++;
	}

	void Ruta::desplazar(double dx, double dy, double maxx, double maxy, double minx, double miny){
		
		TLista tmp = l;
		double cx,cy;

		while(tmp != NULL){
			cx = tmp -> p.dx();
			cy = tmp -> p.dy();

			if((cx <= maxx)&&(cx >= minx)&&(cy <= maxy)&&(cy >= miny)){
				tmp -> p.desplazar(dx,dy);
			}
			tmp = tmp -> sig;
		}
	}

	double Ruta::distanciaTotal()const{
		
		double ttl;
		if(ne >= 2){
			TLista tmp1 = l;
			TLista tmp2 = l -> sig;
			
			while(tmp2 != NULL){
				ttl = ttl + tmp1 -> p.distancia(tmp2 -> p);
				tmp1 = tmp2;
				tmp2 = tmp2 -> sig;
			}	
		}else{
			ttl = -1;
		}

		return ttl;
	}

	bool Ruta::esInverso(const Ruta &rut)const{

		bool est = false;
		int cont = 0,j = 0;
		if(ne == rut.npuntos() ){
			est = true;
			TLista tmp1 = l;

			while(est){
				while(cont < ne && est){
					for(int i = 0 ; i < ne-cont ; i++){
						tmp1 = tmp1 -> sig;
					}
					if(tmp1 -> p.dx() != rut.buscarPto(j).dx() || tmp1 -> p.dy() != rut.buscarPto(j).dy()){
						est = false;
					}
					cont++;
					j++;
					tmp1 = l;
				}				
			}
		}

		return est;

	}

	int Ruta::npuntos()const{
		return ne;
	}

	Punto Ruta::buscarPto(int pos)const{
		TLista tmp = l;
		int i = 0;
		Punto pto;

		if(pos < ne){
			while(i < pos){
				tmp = tmp -> sig;
				i++;
			}

			pto = tmp -> p;
		}

		return pto;
	}

	void Ruta::eliminarCamino(const Punto &pto){
		TLista tmp = l;

		while((tmp != NULL) && (tmp -> p.dx() != pto.dx()) && (tmp -> p.dy() != pto.dy())){
			tmp = tmp -> sig;
		}

		if(tmp != NULL){
			borrarTodo();
		}
	}



	

}
