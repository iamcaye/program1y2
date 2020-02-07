#include "mod.h"

using namespace std;

namespace MConj{

	Conj::Conj()
	{
		ne=0;
	}

	Conj(const Conj &c)
	{
		ne = c.ne;
		for(int n = 0 ; n < ne ; n++){
			datos[n] = c.datos[n] ;
		}
	}

	void Conj::vaciar()
	{
		ne = 0;
	}

	bool Conj::esta(string &p)const
	{
		int n = 0;
		while(n < ne && datos[n] != p ){
			n++;
		}
		
		return n<ne;
	}

	void Conj::insertar(string &p)
	{
		if(!esta(p)){
			datos[ne] = p;
			ne++;
		}else{
			cout << "Ese numero ya esta en el conjunto." << endl;
		}
	
	}

	void Conj::escribir()const
	{
		int n;
		
		cout << "Los numeros del conjunto son:" << endl;
	
		for (n = 0 ; n < ne ; n++){
			cout << datos[n] << endl;
		}

	}
}
