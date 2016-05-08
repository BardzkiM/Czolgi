#include "Pocisk.h"



Pocisk::Pocisk(int x, int y, int rot)
{
	this->texturel.loadFromFile("images/pociskl.png");
	this->textureu.loadFromFile("images/pocisku.png");
	this->texturer.loadFromFile("images/pociskr.png");
	this->textured.loadFromFile("images/pociskd.png");
	this->angle = rot;
	setTexture();
	sf::Vector2u pociskSize(texture.getSize());
	this->width = pociskSize.x;
	this->height = pociskSize.y;
	this->x = x - width/2;
	this->y = y - height/2;
	this->movement = 8;
	
	
	//setRotation();
}


Pocisk::~Pocisk()
{
}
void Pocisk::setTexture()
{
	if (this->angle == 0)
	{
		this->texture = this->texturel;
	}
	if (this->angle == 90)
	{
		this->texture = this->textureu;
	}
	if (this->angle == 180)
	{
		this->texture = this->texturer;
	}
	if (this->angle == 270)
	{
		this->texture = this->textured;
	}
}
