#include "pelota.h"
#include "ioconsole.hpp"

namespace jTenis{

	Pelota::Pelota(){
	
		text_info info;
		cio >> info;

		xmin = info.winleft;
		xmax = info.winright;
		ymin = info.wintop;
		ymax = info.winbottom;	
	}

	void Pelota::defPos(int col, int fil, int d){

		const int DX[] = {1,1,-1,-1};
		const int DY[] = {-1,1,1-1};
		
		x = col;
		y = fil;

		dx = DX[d];
		dy = DY[d];
	}
	
	bool Pelota::fueraIzq()const{
		return x < xmin;
	}
	
	bool Pelota::fueraDer()const{
		return x > xmax;
	}

	bool Pelota::fuera()const{
		return fueraIzq() || fueraDer();
	}

	void Pelota::mover(){
		paso++;
		if(paso > VEL){
			paso = 0;

			cio << cursorxy(x,y) << ' ';

			x = x + dx;
			y = y + dy;

			if(y == ymin && dy == -1){
				dy = +1;
			}

			if(y == ymax && dy == 1){
				dy = -1;
			}

			cio << cursorxy(x,y) << DIB;
		}
	}

	void Pelota::rebotar(const Paleta &pI, const Paleta &pD){

			if(dx == -1 && pI.toca(x,y)){
				dx = +1;
			}

			if(dx == 1 && pD.toca(x,y)){
				dx = -1;
			}
			
	}

}
