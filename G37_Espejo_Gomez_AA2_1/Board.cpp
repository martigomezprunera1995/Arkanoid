#include "Board.h"

Board::Board()
{
	//Comprobar si hemos llegado a ";"
	char aux;
	std::string tamanyoTablero;
	std::string num_rowsS;
	std::string num_columnsS;
	std::string bloquesS;

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
	pos_yBall = rand() % ((num_rows / 2) + 1) ;

	//LASPOSITION
	auxLeft = 0;
	auxRight = 0;

	//Ball
	p[pos_xBall][pos_yBall] = '*';

	//Colisiones
	izquierda = false;
	abajo = true;
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
	if (pos_y - 1 <= 0)
	{
		//NEWSPACE
		p[pos_x][1] = ' ';

		//RESTEAMOS VARIABLES
		pos_y = num_columns - 2;

		//SEGUNDA ITERACION
		auxLeft++;
	}
	else if (auxLeft == 1)
	{
		//NEWSPACE
		p[pos_x][3] = ' ';
		//TERCERA ITERACION
		auxLeft++;
	}
	else if (auxLeft == 2)
	{
		//NEWSPACE
		p[pos_x][2] = ' ';
		//VUELTA AL INICIO
		auxLeft =0;
	}
	else
	{
		//NEWSPACE
		p[pos_x][pos_y + 2] = ' ';
	}

	//SI NO HA LLEGADO AL L�MITE DEL MAPA
	p[pos_x][pos_y - 1] = '-';

	//RESETEAMOS VARIABLES
	pos_y--;
}

void Board::newPosRight()
{

	if (pos_y + 2 >= (num_columns - 2))
	{
		//NEWSPACE
		p[pos_x][num_columns - 2] = ' ';

		//RESTEAMOS VARIABLES
		pos_y = -2;

		auxRight++;
	}
	else if (auxRight == 1)
	{
		//NEWSPACE
		p[pos_x][num_columns - 4] = ' ';
		auxRight++;
	}
	else if (auxRight == 2)
	{
		//NEWSPACE
		p[pos_x][num_columns - 3] = ' ';
		auxRight = 0;
	}
	else
	{
		//NEWSPACE
		p[pos_x][pos_y] = ' ';
	}

	//SI NO HA LLEGADO AL L�MITE DEL MAPA
	p[pos_x][pos_y + 3] = '-';
	//RESETEAMOS VARIABLES
	pos_y++;

}

void Board::newPosBall(int x, int y)
{

	//NEWSPACE
	if (pos_xBall > bloques)
	{
		p[pos_xBall][pos_yBall] = ' ';
	}
	else
	{
		p[pos_xBall][pos_yBall] = '@';
	}

	//CONTROL CHOQUES
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
	else if (y + 1 >= (num_columns - 1))
	{
		derecha = true;

		//Resetamos bools
		arriba = false;
		izquierda = false;
		abajo = false;
	}
	else if ((x + 1 >= pos_x))
	{
		if ((y == pos_y + 1))
		{
			abajo = true;

			//Resetamos bools
			arriba = false;
			izquierda = false;
			derecha = false;
		}
		else if (y == pos_y + 2)
		{
			abajo = true;

			//Resetamos bools
			arriba = false;
			izquierda = false;
			derecha = false;
		}
		else if (y == pos_y + 3)
		{
			abajo = true;

			//Resetamos bools
			arriba = false;
			izquierda = false;
			derecha = false;
		}
	}
	else if (x + 1 >= (num_rows - 1))
	{ 
		system("pause");
	}

	//NUEVA VELOCIDAD
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
	
	//A�ADIMOS AL TABLERO
	p[pos_xBall][pos_yBall] = '*';

	std::cout << x << std::endl;
	std::cout << num_rows - 1 << std::endl;
}

Board::~Board()
{
	if (p != nullptr)
	{
		delete[] p;
		p = nullptr;
	}
}

