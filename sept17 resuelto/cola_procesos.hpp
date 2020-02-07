#ifndef __COLA_PROCESOS__
#define __COLA_PROCESOS__

#include "proceso.hpp"
#include <array>

namespace bblProgII {
class ColaProcesos {
public:
	// Inicializa la cola de procesos a cola vacía
	ColaProcesos();

	// Constructor de copia de la clase
	ColaProcesos(const ColaProcesos &c);

	// Indica si la cola está o no vacía
	bool colaVacia()const;

	// Indica si la cola está o no llena
	bool colaLlena()const;

	// Devuelve el número de procesos
	// encolados en la cola
	unsigned numProcesos()const;

	// Consulta el frente (primer elmento) de la cola
	// PRECONDICIÓN: la cola no está vacía
	void frente(Proceso &p)const;

	// Encola (por el final) un proceso en la cola
	// PRECONDICIÓN: la cola no está llena
	void encolar(const Proceso &p);

	// Desencola (elimina por el frente) un proceso
	// PRECONDICIÓN: la cola no está vacía
	void desencolar();

	// Indica si un proceso, con identificador 'proc_id',
	// está almacenado (true) o no (false) en la cola.
	bool estaEnCola(unsigned proc_id)const;
private:
	// A DEFINIR POR EL ALUMNO
	static const int MAX_NUM_PROCESOS = 10;

	typedef Proceso TColaProces[MAX_NUM_PROCESOS];

	TColaProces l;
	int num_procesos;
};
}
#endif
