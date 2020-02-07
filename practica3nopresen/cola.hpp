//Cayetano Biehler Pollaci
#ifndef COLA_H
#define COLA_H

using namespace std;

namespace prEvaluable{

	template<typename TCola, int max>
	class Cola{
		public:
			Cola(){
				cabeza = 0;
				fin = 0;
			

			void encolar(int num){

				if(fin<max){
					c[fin] = num;
					fin++;
				}else{
					if(cabeza != 0){
						fin = 0;
						c[fin] = num;
					}else{  
						std::cout << "La cola esta llena" << std::endl;
					}
				}
			}

			double desencolar(){
				double x = -1;
			
				if(!vacia()){
					x = c[cabeza];
					c[cabeza] = 0;
					cabeza++;
				}
				return x;
			}

			bool vacia(){
				return fin==cabeza;
			}

		private:

			static const int max = 5;
			typedef TCola TLista [max];
			TLista c;
			int cabeza, fin;

	};

}

#endif
