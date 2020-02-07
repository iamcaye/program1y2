
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	string nomE, nomS, palabra, cod;
	ifstream FEntrada;
	ofstream FSalida;

	cout << "Introduzca el nombre del archivo que quiere descodificar:" << endl;
	cin >> nomE;

	nomS = nomE + ".cod" ;

	FEntrada.open(nomS);
	FSalida.open(nomE);

	FEntrada >> palabra;
	
	while(FEntrada.good()){
		for(unsigned i=0 ; i < palabra.size() ; i++){
			cod[i] = palabra[i] - 3;
			FSalida << cod[i];
		}

		if(FSalida.good()){
			FSalida << endl;
		}	
		FEntrada >> palabra;
	}

	if(FEntrada.eof() && !FSalida.fail()){
		cout << nomE << " se ha descodificado correctamente." << endl;
	}else{
		cout << "Ha habido un problema en el proceso de descodificacion." << endl;
	}
	
	return 0;
}
