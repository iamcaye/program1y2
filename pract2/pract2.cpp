#include <iostream>
#include "mod.h"


using namespace std;
using namespace MConj;

int main()
{
	Conj c;
	string p;

	c.vaciar();

	cout << "Introduzca un numero, hasta 'fin'." << endl;
	getline( cin, p, '\n' );

	while(p != "fin"){
		c.insertar(p);

		getline( cin, p, '\n' );
	}

	c.escribir();	

	return 0;

}
