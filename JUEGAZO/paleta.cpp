#include "paleta.h"
#include "ioconsole.hpp"

namespace jTenis{

	Paleta::Paleta(){
		text_info info;
		cio >> info;

		ymin = info.wintop + TAM;
		ymax = info.winbottom - TAM;
	}

	void Paleta::defPos(int col, int fil){
		x = col;
		y = fil;
		dy = 0;
		paso = 0;
	}

	void Paleta::arriba(){
		dy = -1;
	}

	void Paleta::abajo(){
		dy = 1;	
	}
	void Paleta::dibujar(char c)const{
		for(int i = y - TAM ; i <= y + TAM ; i++){
			cio << cursorxy(x,i) << c;
		}
	}


	void Paleta::mover(){
		paso++;
		if(paso > VEL){
			paso = 0;
			dibujar(' ');
			y = y + dy;
			if(y < ymin){
				y = ymin;
				dy = 0;
			}
			if(y > ymax){
				y = ymax;
				dy = 0;
			}
			dibujar(DIB);
		}//i f
	}

	bool Paleta::toca(int col, int fil)const{
		return ((col <= x+1) && (col >= x-1) && (fil >= y - TAM) && (fil <= y + TAM));
	}

}
