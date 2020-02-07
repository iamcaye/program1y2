
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int NMAX = 50;

typedef string TLista[NMAX];

typedef struct {
	TLista datos;
	int ne;
}TConj;

void convertir (const TConj &c, string nombre);
void comparar(const TConj &a, const TConj &b);

int main()
{
	string Nom1, Nom2, NomS;
	TConj fich1, fich2;

	cout << "Introduzca los nombres de los ficheros para comparar:" << endl;
	cout << "Fichero 1: " ;
	cin >> Nom1;
	
	cout << "Fichero 2: ";
	cin >> Nom2;

	cout << "Introduzca el fichero de destino: ";
	cin >> NomS;

	convertir(fich1, Nom1);
	convertir(fich2, Nom2);
	
	

	

	return 0;
}

void convertir (const TConj &c, string nombre)
{
	ifstream FEntrada;
	unsigned i = 0;

	FEntrada.open(nombre);

	FEntrada << c.datos[i];

	while(FEntrada.good()){
	i++;

	FEntrada << c.datos[i];
	}

	c.ne = i;

	FEntrada.close();

}

void comparar(const TConj &a, const TConj &b, string nombre)
{

	ofstream FSalida;
	bool noesta = true;
	unsigned i,j;

	FSalida.open(nombre);

	for(i = 0 ; i < a.ne ; i++){
		for(j = 0 ; j < b.ne ; j++){
			if(a.datos[i] == b.datos[j]){
				noesta = false;
			}
		}
		if(noesta){
			FSalida >> a.datos[i] << endl;
		}
	}

	FSalida.close();
}
