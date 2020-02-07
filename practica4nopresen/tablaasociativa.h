#ifndef TASOC_H
#define TASOC_H

namespace tads{

	class TablaAsociativa{
		public:
			TablaAsociativa();
			~TablaAsociativa();
			TablaAsociativa(const TablaAsociativa &o);
			TLista duplicar(const TablaAsociativa &o);
			unsigned fHash (const std::string &c);
			void inlcuir (const std:: string &cl, const std::string &va);
			std::string obtener (const std::string &cl)const;
			bool existe (const std::string &cl)const;
			void borrar (const std::string &cl);
			void grabar (const std::string &f)const;
			//void cargar (const std::string &f)const;
		
		private:
			const int TAM = 100;
			
			struct TNodo{
			std::string clave, valor;
			TNodo* sig;
			};
			
			typedef TNodo* TLista;
			typedef TLista THash[TAM];
			
			THash tabla;
	};
}

#endif
