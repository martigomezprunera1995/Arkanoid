#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include <ctime>
#include <Windows.h>

//CONSTANTES

class Board
{
public:

	//Variables
	char **p;
	int num_rows;
	int num_columns;

	//Linea de bloques
	int bloques;

	//Player
	int pos_x;
	int pos_y;

	//Ball
	int pos_xBall;
	int pos_yBall;

	//Colisiones
	bool derecha;
	bool arriba;
	bool abajo;
	bool izquierda;

	//Functions
	void printTablero();
	void newPosLeft();
	void newPosRight();
	void newPosBall(int x, int y);

	//Constructors
	Board();

	//Destructors
	~Board();

private:

};
