#include "Board.h"

Board::Board()
{
	//Comprobar si hemos llegado a ";"
	char aux;
	std::string tamanyoTablero;
	std::string num_rowsS;
	std::string num_columnsS;
	std::string bloquesS;

	//Int
	int bloques;

	//Contador para las variables
	int counter = 0;

	std::ifstream fileConfig("config.txt");
	if (fileConfig.is_open())
	{
		while (!fileConfig.eof())
		{
			if (counter == 0)
			{
				std::getline(fileConfig, tamanyoTablero);
				counter++;
			}
			else if (counter == 1)
			{
				std::getline(fileConfig, bloquesS);
				counter++;
			}
		}
	}
	fileConfig.close();

	//Arreglamos array
	counter = 0;
	for (int i = 0; i < tamanyoTablero.size(); i++) {
		if (counter == 0)
		{
			if (tamanyoTablero[i] == ';')
			{
				counter++;
			}
			else
			{
				num_columnsS += tamanyoTablero[i];
			}
		}
		else if (counter == 1)
		{
			if (tamanyoTablero[i] == ';')
			{
				counter++;
			}
			else
			{
				num_rowsS += tamanyoTablero[i];
			}
		}
	}

	//STRING TO INT
	num_columns = std::stoi(num_columnsS);
	num_rows = std::stoi(num_rowsS);
	bloques = std::stoi(bloquesS);

	//Creamos array dinamico
	p = new char*[num_rows];
	for (int i = 0; i < num_rows; i++)
	{
		p[i] = new char[num_columns];
	}

	//Inicializamos
	for (int i = 0; i < num_rows; i++)
	{
		for (int j = 0; j < num_rows; j++)
		{
			//LINEA HORIZONTAL, VERTICAL, ESPACIOS, BLOQUES
			if ((i == 0) || (i == (num_rows - 1)))
			{
				p[i][j] = '_';
			}
			else if ((j == 0) || (j == (num_rows-1)))
			{
				p[i][j] = '|';
			}
			else if ((i<=bloques))
			{
				p[i][j] = '@';
			}
			else
			{
				p[i][j] = ' ';
			}
		}
	}

	//POS INICIAL JUGADOR
	pos_x = num_columns - 3;
	pos_y = num_rows / 2;

	//JUGADOR
	p[pos_x][pos_y] = '-';
	p[pos_x][pos_y+1] = '-';
	p[pos_x][pos_y+2] = '-';

	//POS INICIAL PELOTA
	pos_xBall = num_columns - 5;
	pos_yBall = num_rows / 2;

	//Ball
	p[pos_xBall][pos_yBall] = '*';

	//Colisiones
	izquierda = false;
	abajo = false;
	derecha = false;
	arriba = false;
}

void Board::printTablero()
{
	//COLOR
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < num_rows; i++)
	{
		for (int j = 0; j < num_rows; j++)
		{
			if (p[i][j] == '_')
			{
				SetConsoleTextAttribute(color, 10);
			}
			else if (p[i][j] == '|')
			{
				SetConsoleTextAttribute(color, 10);
			}
			else if (p[i][j] == '@')
			{
				SetConsoleTextAttribute(color, 9);
			}
			else if (p[i][j] == '*')
			{
				SetConsoleTextAttribute(color, 4);
			}
			std::cout << p[i][j];
		}
		std::cout << std::endl;
	}
}

void Board::newPosLeft()
{
	//NEWPOS
	p[pos_x][pos_y - 1] = '-';

	//NEWSPACE
	p[pos_x][pos_y + 2] = ' ';

	//RESETEAMOS VARIABLES
	pos_y--;
}

void Board::newPosRight()
{
	//NEWPOS
	p[pos_x][pos_y + 3] = '-';

	//NEWSPACE
	p[pos_x][pos_y] = ' ';

	//RESETEAMOS VARIABLES
	pos_y++;

}

void Board::newPosBall(int x, int y)
{

	//NEWSPACE
	p[pos_xBall][pos_yBall] = ' ';

	if (y - 1 <= 0) 
	{
		izquierda = true;

		//Resetamos bools
		derecha = false;
		arriba = false;
		abajo = false;
	}
	else if (x - 1 <= 0)
	{
		arriba = true;

		//Resetamos bools
		derecha = false;
		izquierda = false;
		abajo = false;
	}
	else if (y + 1 >= (num_columns-1))
	{
		derecha = true;

		//Resetamos bools
		arriba = false;
		izquierda = false;
		abajo = false;
	}
	else if ((x + 1 >= pos_x) && (y - 1 == pos_y))
	{
		abajo = true;

		//Resetamos bools
		arriba = false;
		izquierda = false;
		derecha = false;
	}

	if (izquierda == true)
	{
		//Cambiamos velocidad
		pos_yBall++;
		pos_xBall--;
	}
	else if (arriba == true)
	{
		//Cambiamos velocidad
		pos_yBall++;
		pos_xBall++;
	}
	else if (derecha == true)
	{
		//Cambiamos velocidad
		pos_yBall--;
		pos_xBall++;
	}
	else if (abajo == true)
	{
		pos_yBall--;
		pos_xBall--;
	}
	else
	{
		pos_yBall--;
		pos_xBall--;
	}


	std::cout << "Ball Y:" << y << std::endl;
	std::cout << "Ball X:" << x << std::endl;
	std::cout << "Player X: " << pos_x << std::endl;
	std::cout << "Player Y: " << pos_y << std::endl;
	
	//AÑADIMOS AL TABLERO
	p[pos_xBall][pos_yBall] = '*';


}

Board::~Board()
{
	if (p != nullptr)
	{
		delete[] p;
		p = nullptr;
	}
}

