#include "Mapa.h"





Mapa::Mapa()
{
	
	initializeMap();
}


Mapa::~Mapa()
{
}


void Mapa::initializeMap()
{
	this->texture.loadFromFile("images/mapa.png");


	int tablicaPrzeszkod[15][20] = {
		{0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0},
		{0,1,0,0,0,0,0,1,0,1,1,0,1,0,0,0,0,0,1,0},
		{0,0,0,1,0,1,0,0,0,1,1,0,0,0,1,0,1,0,0,0},
		{0,1,0,1,0,1,0,1,0,0,0,0,1,0,1,0,1,0,1,0},
		{0,1,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,1,0},//4
		{0,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0},
		{0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
		{1,1,0,1,1,1,1,0,0,1,1,0,0,1,1,1,1,0,1,1},
		{0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0},
		{0,1,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,1,0},
		{0,1,0,1,0,1,0,1,0,0,0,0,1,0,1,0,1,0,1,0},
		{0,0,0,1,0,1,0,0,0,1,1,0,0,0,1,0,1,0,0,0},
		{0,1,0,0,0,0,0,1,0,1,1,0,1,0,0,0,0,0,1,0},
		{0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0},
	};


	//przeszkody.push_back(Przeszkoda(50, 50));
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if(tablicaPrzeszkod[j][i]==1)
				przeszkody.push_back(Przeszkoda(i*60,j*60));
		}
	}
	
}

void Mapa::setPlayers()
{

}