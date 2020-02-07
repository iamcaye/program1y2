
#ifndef MOD_H
#define MOD_H

	#include <iostream>
	#include <string>

	namespace MConj{


	class Conj{
	public:
		Conj();
		Conj(const Conj &c);
		~Conj();
		Conj& operator=(const Conj &c)

//SUBPROGRAMAS--Declaración.

		void vaciar();
		void insertar(std::string &p);
		bool esta(std::string &p)const;
		void escribir ()const;

	private:
//CONSTANTES

		static const int MAX_LISTA = 10;

//ESTRUCTURAS

		typedef std::string TLista[MAX_LISTA];

		int ne=0;
		TLista datos;
		};
	}
#endif

