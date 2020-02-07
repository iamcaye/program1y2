

	int num_colas()const{

		int cont;
		TLista tmp;

		tmp = l;
		cont = 0;

		while(tmp != NULL){
			cont++;
			tmp = tmp -> sig;		
		}
		return cont;
	}

	std::vector<unsigned> num_procesos()const{
		std::vector<unsigned> res;
		TLista tmp;
		unsigned np;

		tmp = l;

		while(tmp != NULL){
			np = tmp -> cola.numProcesos();
			res.pushback();
			tmp = tmp -> sig;
		}
	}

	void consultar_proceso(unsigned id_proceso, Proceso &p, bool &existe)const{
		TLista tmp;
		ColaProcesos co(tmp -> cola)

		tmp = colas;

		while(tmp != NULL && !tmp -> cola.estaEnCola(id_proceso)){
			tmp = tmp -> sig;
		}

		if(tmp == NULL){
			existe = false;
		}else{
			existe = true;
		}

		co.frente(p);

		while(p.consultar_id() != id_proceso){
			co.desencolar();
			co.frente();		
		}
		
	}

	void escribir()const{
		TLista tmp;

		tmp = colas;

	 	while(tmp != NULL){
			ColaProcesos co(tmp -> colas);
			while(!co.colaVacia()){
				co.frente();
				std::cout << p.consultar_id() << std::endl;
				std::cout << consultar_prioridad() << std::endl;
			}
		}
	}

	void leer_fichero(const std::string &nom_fic){
		std::ifstream fi;
		unsigned id, pri;
		double mem,tcpu;
		Proceso p;
		bool ok;

		fi.open(nom_fic.c_str());
		if(fi.good()){
			fi>>id>>pri>>mem>>tcpu;

			while(!fi.eof()){
				p(id,pri,mem,tcpu);
				fi >> id >> pri >> mem >> tcpu;
			}
		}

		fi.close();
	}


