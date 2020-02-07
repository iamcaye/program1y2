#include <iostream>
#include <vector>
#include "planificador.hpp"

using namespace std;
using namespace bblProgII;

int main() {
	Planificador plan;

	plan.leer_fichero("procesos.txt");
	cout << "ESTADO ACTUAL DEL PLANIFICADOR: " << endl;
	cout << "NÚMERO DE COLAS: " << plan.num_colas() << endl;
	cout << "NÚMERO TOTAL DE PROCESOS ENCOLADOS: " << endl;
	vector<unsigned> n_proc = plan.num_procesos();
	for (unsigned i = 0; i < unsigned(n_proc.size()); i ++) {
		cout << "Cola 0: " << n_proc[i] << endl;
	}
	plan.escribir();

	Proceso p;
	bool existe;
	cout << "Consultando proceso... 333... " << endl;
	plan.consultar_proceso(333, p, existe);
	if (existe) {
		cout << "Prioridad: " << p.consultar_prioridad() << endl;
		cout << "Memoria: " << p.consultar_memoria() << endl;
		cout << "Tiempo cpu: " << p.consultar_tiempo_cpu() << endl << endl;
	}

	Planificador otro_plan(plan); // Constructor de copia

	while (plan.num_colas() > 0) {
		unsigned id;
		bool exito;
		Proceso p;
		plan.desencolar(id, exito);
		cout << "Proceso desencolado... " << id << endl;
	}
}