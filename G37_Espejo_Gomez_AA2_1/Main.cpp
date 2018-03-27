#include "Board.h"

void main()
{
	//Creacion del board
	Board b1;

	//X del jugador
	int x;

	//Bool finalJuego
	bool final = false;

	//Control de teclado
	while (final!=true)
	{
		//Limpiamos tablero
		Sleep(100);
		system("cls");

		//Recogemos posicion
		x = b1.pos_y;

		//Printamos tablero
		b1.printTablero();
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			final = true;
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			b1.newPosLeft();
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			b1.newPosRight();
		}
	}
}