#include "pilaconpunteros.hpp"
#include <iostream>

using namespace std;
using namespace Pilapunt;

typedef Pila<int> Pilar;

void ej(Pilar p);

int main(){

	int x;
	Pilar k;
	k.apilar(4);
	ej(k);

	x = k.desapilar();
	cout << x;
	return 0;
}

void ej(Pilar p){

	int x;

	p.apilar(5);
	p.apilar(6);
	p.apilar(7);

	x = p.desapilar();

	cout << x << endl;

}
