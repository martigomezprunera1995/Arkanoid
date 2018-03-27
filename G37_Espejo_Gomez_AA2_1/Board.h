#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include <Windows.h>

//CONSTANTES

class Board
{
public:

	//Variables
	char **p;
	int num_rows;
	int num_columns;

	//Player
	int pos_x;
	int pos_y;

	//Functions
	void printTablero();
	void newPosLeft();
	void newPosRight();

	//Constructors
	Board();

	//Destructors
	~Board();

private:

};
