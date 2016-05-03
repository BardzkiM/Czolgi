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
}

void Mapa::setPlayers()
{

}