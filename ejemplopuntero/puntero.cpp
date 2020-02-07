#include <iostream>
#include <cstdlib>


using namespace std;

struct TNodo{
	int dato;//tipo base del puntero
	TNodo* sig;
};			//Lista enlazada. IMPORTANTE ENTENDER PQ LO VAMOS A USAR EN TODA LA ASIGNATURA.

typedef TNodo* TLista;

//Declaracion de un puntero.
//typedef int* TPunt;

//ALGORITMOS.Definicion

void inicializar(TLista &l);
void insertarPrimero(TLista &l, int v);
void borrarPrimero(TLista &l);
void borrarTodos(TLista &l);

int main(){

//TEORIA BASICA DE PUNTEROS
	/*p1 = new int;

	TPunt p1,p2,p3;

	int x;


	*p1 = 5;

	p2 = new int;

	*p2 = 5;

	delete p1;	//borrar puntero

	p2 = NULL;	//anular un puntero. "Hacer q un puntero no apunte a nada". TIENE Q IR EN MAYUSCULAS

	p3 = &x;	//almacenar en un puntero una variable estatica.

	*/


	//////////////////////////------PILA DE ENTEROS------///////////////////////////

	return 0;
	
} 


//ALGORITMOS.Desarrollo;

void inicializar(TLista &l){

	l = NULL;	//vaciar el nodo

}

void insertarPrimero(TLista &l, int v){

	TLista temp;				//variable temporal para no perder la lista

	temp = new TNodo;			//creamos una nueva variable anonima a la q en el siguiente paso le daremos un valor

	temp -> dato = v;			//(*temp).dato = v; ESTA FORMA NO LA USA NI EL TATO. Los programadores de calité usan la otra.
	
	temp -> sig = l;			//metemos temp en la lista. La estanos uniendo al nodo
	
	l = temp;				//copiamos temp en el nodo pa q tenga el valor v
}

void borrarPrimero(TLista &l){

	if(l != NULL){
		TLista temp;				//variable temporal para no perder la lista.
					
		temp = l;				//copiamos la informacion de l en la variable temporal.

		l = l -> sig;				//union del puntero con el siguiente nodo.

		delete temp;				//eliminamos el nodo para borrar el primer dato de la lista.
	}else{

		cout << "ERROR 1" << endl;
		exit(1);

	}

}

void borrarTodos(TLista &l){

	TLista temp;

	while(l != NULL){

		temp = l;

		l = l -> sig;
	
		delete temp;

	}

}


