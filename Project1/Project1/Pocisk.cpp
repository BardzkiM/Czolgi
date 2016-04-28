#include "Pocisk.h"



Pocisk::Pocisk(int x, int y, int rot)
{
	this->texturel.loadFromFile("images/pociskl.png");
	this->textureu.loadFromFile("images/pocisku.png");
	this->texturer.loadFromFile("images/pociskr.png");
	this->textured.loadFromFile("images/pociskd.png");
	sf::Vector2u pociskSize(texture.getSize());
	this->width = pociskSize.x;
	this->height = pociskSize.y;
	this->x = x;
	this->y = y;
	this->angle = rot;
}


Pocisk::~Pocisk()
{
}
