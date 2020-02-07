
#include <iostream>
#include "pila.hpp"
#include <cstdlib>
#include <string>

using namespace std;
using namespace mPila;

typedef Pila <int, 100> TPE;

int main()
{
	TPE pila;

	string tok;
	int r, o1, o2;

	cin >> tok;
	while(tok != "="){

	switch(tok[0]){
		case '+' :
			o2 = pila.desapilar();
			o1 = pila.desapilar();
			r = o1 + o2;
			pila.apilar(r);
			break;

		case '-' :
			o2 = pila.desapilar();
			o1 = pila.desapilar();
			r = o1 - o2;
			pila.apilar(r);
			break;

		case '*' :
			o2 = pila.desapilar();
			o1 = pila.desapilar();
			r = o1 * o2;
			pila.apilar(r);
			break;

		default :
			r = stoi(tok);
			pila.apilar(r);


	}
		cin >> tok;
	}

	r = pila.desapilar();

	cout << "El resultado es: " << r << endl;

	return 0;
}
