#include <iostream>
#include <string>
#include <array>
#include <cstdlib>

using namespace std;

//CONSTANTES

const int MAX_LISTA = 10;

//ESTRUCTURAS

typedef array <string, MAX_LISTA> TLista;

typedef struct {
	int ne=0;
	TLista datos;
}TConj;

//SUBPROGRAMAS--Declaración.

void vaciar(TConj &c);
void insertar(TConj &c, string &p);
bool esta(const TConj &c, string &p);
void escribir (const TConj &c);

//MAIN

int main()
{
	TConj c;
	string p;

	vaciar(c);

	cout << "Introduzca un numero, hasta 'fin'." << endl;
	cin >> p;

	while(p != "fin"){
		insertar(c,p);

		cin >> p;
	}

	escribir(c);	

	return 0;
}

//SUBPROGRAMAS--Código.

void vaciar(TConj &c)
{
	c.ne = 0;
}

bool esta(const TConj &c, string &p)
{
	bool est = false;
	int n = 0;
	while(n < c.ne && c.datos[n] != "fin"){
		if( c.datos[n] == p ){
			est = true;
		}
		n++;
	}
	
	return est;
}

void insertar(TConj &c, string &p)
{
	if(!esta(c,p)){
		c.datos[c.ne] = p;
		c.ne++;
	}else{
		cout << "Ese numero ya esta en el conjunto." << endl;
	}

}

void escribir (const TConj &c)
{
	int n;
	
	cout << "Los numeros del conjunto son:" << endl;

	for (n = 0 ; n < c.ne ; n++){
		cout << c.datos[n] << endl;
	}

}
