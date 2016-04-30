#include "Pocisk.h"



Pocisk::Pocisk(int x, int y, int rot)
{
	this->texturel.loadFromFile("images/pociskl.png");
	this->textureu.loadFromFile("images/pocisku.png");
	this->texturer.loadFromFile("images/pociskr.png");
	this->textured.loadFromFile("images/pociskd.png");
	sf::Vector2u pociskSize(texturel.getSize());
	this->width = pociskSize.x;
	this->height = pociskSize.y;
	this->x = x - width/2;
	this->y = y - height/2;
	this->angle = rot;

	setRotation();
}


Pocisk::~Pocisk()
{
}
