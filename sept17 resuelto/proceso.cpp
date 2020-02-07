#include "proceso.hpp"

namespace bblProgII {
Proceso::Proceso():
	identificador(), prioridad(),
	memoria(), tiempo_cpu() {}

// Constructor que inicializa el proceso
// con todos sus datos (id, prioridad,
// memoria y tiempo_cpu)
Proceso::Proceso(unsigned id, unsigned pri,
                 unsigned mem, double t_cpu):
	identificador(id), prioridad(pri),
	memoria(mem), tiempo_cpu(t_cpu) {}

// Constructor de copia
Proceso::Proceso(const Proceso &p):
	identificador(p.identificador),
	prioridad(p.prioridad),
	memoria(p.memoria),
	tiempo_cpu(p.tiempo_cpu) {}

// Consulta el id del proceso
unsigned Proceso::consultar_id() const {
	return identificador;
}

// Consulta la prioridad del proceso
unsigned Proceso::consultar_prioridad() const {
	return prioridad;
}

// Consulta la memoria empleada por el proceso
double Proceso::consultar_memoria() const {
	return memoria;
}

// Consulta el tiempo de cpu empleado por el
// proceso en su ejecución
double Proceso::consultar_tiempo_cpu() const {
	return tiempo_cpu;
}
}
