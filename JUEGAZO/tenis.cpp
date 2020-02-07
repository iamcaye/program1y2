#include "paleta.h"
#include "pelota.h"
#include "ioconsole.hpp"

using namespace jTenis;
using namespace std;

int main()
{
	Pelota pel;
	Paleta palI, palD;

//Inicializacion del juego

	text_info info;
	int centroX, centroY;
	cio >> info;

	centroX = (info.winleft + info.winright)/2;
	centroY	= (info.winbottom + info.wintop)/2;

	pel.defPos(centroX, centroY, aleatorio(4));
	palI.defPos(info.winleft, centroY);
	palD.defPos(info.winright, centroY);

	cio >> disable_buffer;
	cio << no_cursor;
	cio << clear_screen;

//JUEGAZO

	while(!pel.fuera()){

	//Interaccion objeto
		pel.mover();
		palI.mover();
		palD.mover();
		pel.rebotar(palI, palD);

		cio << flush;

	//Interaccion jugador
		if(cio.kbhit()){
			char tecla;
			cio >> tecla;
	
			switch(tecla){
				case 'q':
					palI.arriba();
					break;
				case 'z':
					palI.abajo();
					break;
				case 'p':
					palD.arriba();
					break;
				case '.':
					palD.abajo();
					break;
			}//switch

		msleep(10);

		}//if	

	}//while

	if(pel.fueraDer()){
	//ganador izq
	cio << cursorxy(centroX-10, centroY) << "Gana jugador izquierda" << endl;
	}

	if(pel.fueraIzq()){
	//ganador der
	cio << cursorxy(centroX-10, centroY) << "Gana jugador derecha" << endl;
	}

	//mensaje fin de juego
	cio << cursorxy(centroX-13, centroY+1) << "GAME OVER" << endl;

	msleep(3000);
	cio << clear_screen;

	return 0;
}
