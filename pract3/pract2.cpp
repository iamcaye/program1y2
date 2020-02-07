#include <iostream>
#include "mod.hpp"


using namespace std;
using namespace MConj;

typedef Conj<string,10> CCad;

int main()
{
	CCad c;
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
