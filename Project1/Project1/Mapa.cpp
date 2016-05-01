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
	this->texture.loadFromFile("mapa.bg");
}

void Mapa::setPlayers()
{

}