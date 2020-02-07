#include "cola_procesos.h"
#include <iostream>

namespace bblProgII{

	ColaProcesos::ColaProcesos():num_procesos(0){}

	ColaProcesos::ColaProcesos(const ColaProcesos &c){
		num_procesos = c.numProcesos();
		Proceso proces;

		for(unsigned i = 0 ; i < c.numProcesos() ; i++){
			proces = c[i];
			l[i] = proces;
		}
	}

	bool ColaProcesos::colaVacia()const{
		return num_procesos == 0;
	}

	bool ColaProcesos::colaLlena()const{
		return num_procesos == MAX_NUM_PROCESOS;	
	}

	unsigned ColaProcesos::numProcesos()const{
		return num_procesos;
	}

	void ColaProcesos::frente(Proceso &p)const{
		if(!colaVacia()){
			//p(l[0].identificador, l[0].prioridad, l[0].memoria, l[0].tiempo_cpu);
			p = l[0];
		}
	} 	

	

}
