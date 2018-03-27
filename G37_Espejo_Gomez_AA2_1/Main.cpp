#include "Board.h"

void main()
{
	//Creacion del board
	Board b1;

	//X del jugador
	int x;

	//X y Y de la pelota
	int xBall;
	int yBall;

	//Bool finalJuego
	bool final = false;

	//Control de teclado
	while (final!=true)
	{
		//Limpiamos tablero
		Sleep(200);
		system("cls");

		//Recogemos posicion
		x = b1.pos_y;

		//Printamos tablero
		b1.printTablero();

		//Control teclas
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

		//Recogemos pos de la pelota
		xBall = b1.pos_xBall;
		yBall = b1.pos_yBall;

		//Movimiento pelota
		b1.newPosBall(xBall, yBall);

	}
}