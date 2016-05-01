#include "Przeszkoda.h"



Przeszkoda::Przeszkoda()
{
	this->texture.loadFromFile("przeszkoda.png");
	sf::Vector2u przeszkodaSize(texture.getSize());
	this->width = przeszkodaSize.x;
	this->height = przeszkodaSize.y;
}


Przeszkoda::~Przeszkoda()
{
}
