#include "Pocisk.h"



Pocisk::Pocisk(int x, int y, int rot)
{
	this->texturel.loadFromFile("images/pociskl.png");
	this->textureu.loadFromFile("images/pocisku.png");
	this->texturer.loadFromFile("images/pociskr.png");
	this->textured.loadFromFile("images/pociskd.png");
	this->angle = rot;
	setTexture();
	sf::Vector2u pociskSize(texturel.getSize());
	this->width = pociskSize.x;
	this->height = pociskSize.y;
	this->x = x;
	this->y = y;
	setStartPosition();
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
void Pocisk::setStartPosition()
{
	if (this->angle == 0)
	{
		this->x = this->x - this->width;
		this->y = this->y + 30 - (this->height / 2);
	}
	if (this->angle == 90)
	{
		this->x = this->x + 30 - (this->width/2);
		this->y = this->y - this->height;
	}
	if (this->angle == 180)
	{
		this->x = this->x + 60;
		this->y = this->y + 30 - (this->height / 2);
	}
	if (this->angle == 270)
	{
		this->x = this->x + 30 - (this->width / 2);
		this->y = this->y + 60;
	}
}