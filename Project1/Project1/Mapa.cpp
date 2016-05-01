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
	this->texture.loadFromFile("map.png");
}

void Mapa::setPlayers()
{

}