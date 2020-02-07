//Cayetano Biehler Pollaci
#include <iostream>
#include <string>
#include "matriz.h"
#include "cola.h"
#include <cstdlib>

using namespace std;
using namespace prEvaluable;

int main()
{
	Cola cola;
	MatrizBidimensional matriz;
	int x, y, valor, opcion1 = 0, opcion2=0;

	do{
		cout << "Que modulo desea probar? MatrizBidimensional(1) o Cola(2)." << endl;
		cout << "Salir(0)" << endl;
		cin >> opcion1;

		if(opcion1==1){
			do{
				cout << "(1)Definir alto y ancho." << endl;
				cout << "(2)Almacenar" << endl;
				cout << "(3)Alto" << endl;
				cout << "(4)Ancho" << endl;
				cout << "(5)Mostrar" << endl;

				cin >> opcion2;

				switch(opcion2){
					case 1:
						cout << "Introduzca un alto y un ancho para su matriz:" << endl;
						cin >> x >> y;
						matriz.definirAlto(x);
						matriz.definirAncho(y);
						break;

					case 2:
						cout << "Introduzca el numero que desea almacenar:" << endl;
						cin >> valor;
						cout << "Introduzca las cordenadas (x,y) donde quiere almacenar el numero" << endl;
						cin >> x >> y;

						matriz.almacenar(x,y,valor);
						break;

					case 3:
						cout << "El alto de la matriz es " << matriz.alto() << endl;
						break;

					case 4:
						cout << "El ancho de la matriz es " << matriz.ancho() << endl;	
						break;

					case 5:
						matriz.mostrar();
						break;
				}	

			}while(opcion2 != 0);

		}else if(opcion1==2){
			do{
				cout << "Introduzca una opcion:" << endl;
				cout << "(1)Encolar" << endl;
				cout << "(2)Desencolar" << endl;
				cin >> opcion2;
				
				switch(opcion2){
					case 1: 
						cout << "Que valor desea introducir en la cola:" << endl;
						cin >> valor;	
						cola.encolar(valor);
						break;

					case 2:
						x = cola.desencolar();
						if(x != -1){
							cout << x <<endl;
						}else{
							cout << "La cola esta llena" << endl;
						}
						break;

					default: 
						cout << "Esa opcion no coincie con ninguna de las anteriores." << endl;
						break;
				}

			}while(opcion2!=0);		

		}else if(opcion1 > 2){
			cout << "Esa opcion no coincide con ninguna de las anteriores." << endl;
		}
		system("cls");
	}while(opcion1!=0);

	return 0;
}
