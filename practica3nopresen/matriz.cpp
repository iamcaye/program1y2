//Cayetano Biehler Pollaci
#include "matriz.h"
#include <iostream>
#include <fstream>


namespace prEvaluable{

	MatrizBidimensional::MatrizBidimensional(){

		anch = 0;
		alt = 0;
	
	}

	void MatrizBidimensional::definirAncho(int num){
		anch = num;
	}

	void MatrizBidimensional::definirAlto(int num){
		alt = num;
	}

	void MatrizBidimensional::almacenar(int x, int y, int valor){
		if(x <= max && y <= max){
			matriz[x][y] = valor;
		}
	}

	double MatrizBidimensional::obtener(int x, int y)const{
		int valor = -1;

		if(x <= max && y <= max){
			if(matriz[x][y] != 0){
				valor = matriz[x][y];
			}
		}
		return valor;
	}

	int MatrizBidimensional::alto()const{
		return alt;
	}

	int MatrizBidimensional::ancho()const{
		return anch;
	}

	void MatrizBidimensional::mostrar()const{
		unsigned x,y;

		for(y = 0 ; y < alt ; y++){
			for (x = 0 ; x < anch ; x++){
				std::cout << matriz[x][y] << '\t';
			}
			std::cout << std::endl;
		}

	}

	void MatrizBidimensional::leerDeFichero(const std::string &nom){
	
		int x, y, valor;
		ifstream FEnt;


		FEnt.open(nom.v_str());
		
		FEnt << anch << alt << endl;

		definirAlto(alt);
		definirAncho(anch);

		FEnt << x << y << valor;
		almacenar(x,y,valor);
		while(!FEnt.good()){
			FEnt << x << y << valor;
			almacenar(x,y,valor);
		}	
	
		FEnt.close();		
	}
	
	void MatrizBidimensional::escribirAFichero(const std::string &nom)const{

		unsigned x,y;
		std::ofstream FSal;

		std::FSal.open(nom.v_str());
		
		std::FSal >> ancho() >> alto() >> std::endl;

		for(x = 0 ; x < anch ; x++){
			for(y = 0 ; y < alt ; y++){
				if(matriz[x][y] != 0){
					std::FSal >> x >> y >> matriz[x][y] >> std::endl;
				}
			}
		}	
	
		std::FSal.close();		
	}

	

}
