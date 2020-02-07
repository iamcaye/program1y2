#ifndef __PLANIFICADOR__
#define __PLANIFICADOR__

#include "proceso.hpp"
#include "cola_procesos.hpp"

#include <vector>

namespace bblProgII {
class Planificador {
public:
	// Constructor por defecto:
	// lista de colas vacía
	Planificador();

	// Constructor de copia
	Planificador(const Planificador &p);

	// Destructor
	~Planificador();

	// Si el identificador del proceso no existe
	// en la lista (vector) de identificadores
	// de procesos del planificador, se encola
	// el proceso en la cola de procesos
	// correspondiente a su prioridad. Si la cola para esa
	// prioridad no existe, se crea esa nueva
	// cola (nodo) en el planificador y el proceso
	// se encola en esa nueva cola. La nueva cola
	// debe insertarse en orden creciente de
	// prioridad de los procesos que esa cola
	// guarda (siendo 0 la máxima prioridad).
	// Si la cola de procesos para esa prioridad ya
	// existe, el proceso se encola en ella.
	// Si el proceso se ha podido encolar, se devuelve true
	// a través de 'exito'. Si no, se devuelve false.
	void encolar(const Proceso &p, bool &exito);

	// Si hay colas de prioridad, se desencola el primer
	// proceso de la cola de máxima prioridad (la primera
	// en la lista de colas) y se devuelve el identificador
	// del proceso desencolado a través del parámetro
	// 'id_desencolado', además de true a través del
	// parámetro 'exito'. Si la cola de procesos de donde
	// se ha desencolado el proceso queda vacía,
	// debe eliminarse de la lista de colas.
	// Si la lista de colas estaba vacía, debe devolverse false
	// a través de 'exito'
	void desencolar(unsigned &id_desencolado, bool &exito);

	// Devuelve el número de colas que hay en este momento en
	// el planificador
	unsigned num_colas() const;

	// Devuelve el número total de procesos encolados en todas
	// las colas de prioridad
	std::vector<unsigned> num_procesos() const;

	// Busca el proceso cuyo identificador se pasa como parámetro
	// en la cola de procesos del planificador correspondiente a
	// su prioridad. Si el proceso existe en el planificador,
	// debe devolverse a través del parámetro 'p';
	// además, se devuelve true a través de 'existe'. Si
	// el proceso no está en el planificador, se devuelve false.
	void consultar_proceso(unsigned id_proceso, Proceso &p,
	                       bool &existe) const;

	// Escribe en pantalla la información de todos los procesos
	// encolados en las colas del planificador, en orden de
	// prioridad
	void escribir() const;

	// Lee del fichero que se pasa como parámetro la información
	// de una serie de procesos que deben encolarse en el
	// planificador conforme se leen. El formato del fichero es:
	//	id_proceso_1
	//	prioridad_1
	//	memoria_proceso_1
	//	tiempo_cpu_proceso_1
	//	id_proceso_2
	//	prioridad_2
	//	memoria_proceso_2
	//	tiempo_cpu_proceso_2
	// ...
	void leer_fichero(const std::string &nom_fic);
private:
	// A DEFINIR POR EL ALUMNO
};
}
#endif