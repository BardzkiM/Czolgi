#include "Przeszkoda.h"



Przeszkoda::Przeszkoda(int x, int y)
{
	this->texture.loadFromFile("images/przeszkoda.png");
	sf::Vector2u przeszkodaSize(texture.getSize());
	this->width = przeszkodaSize.x;
	this->height = przeszkodaSize.y;
	this->x = x;
	this->y = y;
	this->movement = 0;
}


Przeszkoda::~Przeszkoda()
{
}
