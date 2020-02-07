#ifndef __PROCESO__
#define __PROCESO__
namespace bblProgII {
class Proceso {
public:
	// Constructor por defecto
	Proceso();

	// Constructor que inicializa el proceso
	// con todos sus datos (id, prioridad,
	// memoria y tiempo_cpu)
	Proceso(unsigned id, unsigned pri, unsigned mem, double t_cpu);

	// Constructor de copia de la clase
	Proceso(const Proceso &p);

	// Consulta el id del proceso
	unsigned consultar_id() const;

	// Consulta la prioridad del proceso
	unsigned consultar_prioridad() const;

	// Consulta la memoria empleada por el proceso
	double consultar_memoria() const;

	// Consulta el tiempo de cpu empleado por el
	// proceso en su ejecución
	double consultar_tiempo_cpu() const;
private:
	unsigned identificador, prioridad, memoria;
	double tiempo_cpu;
};
}
#endif
