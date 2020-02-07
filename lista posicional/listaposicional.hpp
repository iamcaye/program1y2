#ifndef LISTAPOSICIONAL_H
#define LISTAPOSICIONAL_H

template <typename TBase>
class Lista{

	public:
		Pila(){

			l = NULL;

		}

		~Pila(){

			borrarTodo(l);
			
		}

		Pila(const Pila<TBase> &o){
			
			l = duplicar(o.l);
		}

		Pila<TBase>& operator=(const Pila<TBase> &o){		//eliminar todos los nodos de "l" y duplicar o.l

			if(this != &o){
				borrarTodo(l);
				l = duplicar(o.l);
			}

			return *this; 
		}


		int longitud()const{

			int cont = 0;
			TLista tmp = l;

			while(tmp != NULL){

				cont++;
				tmp = tmp -> sig;

			}
			return cont;
		}

		TBase obtener(int pos)const{

			TLista tmp;
			tmp = l;

			while((tmp != NULL)&&(pos > 0)){
				pos--;
				tmp = tmp -> sig;
			}	

			if(tmp == NULL){
				cout << "Error de obtener" << endl;
				exit(1);
			}	
			return tmp -> dato;
		}

		void eliminar(int pos){
		
			TLista tmp, ant;
			tmp = l;
			ant = NULL;

			while((tmp != NULL)&&(pos > 0)){
				pos--;
				ant = tmp;
				tmp = tmp -> sig;
			}//while

			if(tmp == NULL){
				cout << "Error borrarpos" << endl;
				exit(1);			
			}else{
				if(ant == NULL){
					l = l -> sig;
				}else{
					ant -> sig = tmp -> sig;
				}
				delete tmp;
			}

		}

		void almacenar(int pos, const TBase &v){
			TLista tmp;
			tmp = l;

			while((tmp != NULL)&&(pos > 0)){
				pos--;
				tmp = tmp -> sig;
			}	

			if(tmp == NULL){
				cout << "Error de obtener" << endl;
				exit(1);
			}	
			tmp -> dato = v;
		}

		void insertar(int pos, const TBase &v){
			TLista tmp, ant, nue;

			tmp = l;
			ant = NULL;

			while((tmp != NULL)&&(pos > 0)){
				pos--;
				ant = tmp;
				tmp = tmp -> sig;
			}

			nue = new TNodo:
			nue -> dato = v;
			nue -> sig = tmp;
			if(tmp == NULL){
				l = nue;
			}else{
				
				ant -> sig = nue;
			}
		}

		void borrarDuplicados(){

			int pos = 0;
			int rec;

			while(pos < longitud()){
				rec = pos + 1;
				while(rec < longitud()){
					if(obtener(pos) == obtener(rec)){
						eliminar(rec);
					}else{
						rec++;
					}
				} 
				pos++;
			}
		}

	private:
		struct TNodo{
			TBase dato;
			TNodo* sig
		};
		typedef TNodo* TLista;
		TLista l;
		TLista duplicar(TLista li)const{

			TLista res, rec, ult, nue;

			rec = li;
			res = NULL;
			ult = NULL;

			while(rec != NULL){

				nue = new TNodo;
				nue -> dato = rec -> dato;
				nue -> sig = NULL;
			
				if(res == NULL){
					res = nue;
				}else{
					ult -> sig = nue;
				}

				ult = nue;
				rec = rec -> sig;
			}//while
			return res;
		}

		void borrarTodo()const{
			TLista temp;

			while(l != NULL){

				temp = l;

				l = l -> sig;
			
				delete temp;

			}
		}


};

#endif
