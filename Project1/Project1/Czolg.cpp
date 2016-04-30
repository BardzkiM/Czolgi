#include "Czolg.h"




Czolg::Czolg()
{
	this->texturel.loadFromFile("images/tankl.png");
	this->textureu.loadFromFile("images/tanku.png");
	this->texturer.loadFromFile("images/tankr.png");
	this->textured.loadFromFile("images/tankd.png");
	sf::Vector2u tankSize(texturel.getSize());
	this->width = tankSize.x;
	this->height = tankSize.y;
	 

}


Czolg::~Czolg()
{
}


void Czolg::addPocisk()
{
	Pocisk pocisk(this->x, this->y, this->angle);
	this->pociski.push_back(pocisk);
}

void Czolg::move(int direction)
{
	if (this->angle == 0)
	{
		this->x -= 5*direction;
	}
	if (this->angle == 90)
	{
		this->y -= 5 * direction;
	}
	if (this->angle == 180)
	{
		this->x += 5 * direction;
	}
	if (this->angle == 270)
	{
		this->y += 5 * direction;
	}
}
void Czolg::rotate(int angle)
{
	this->angle += angle;
	if (this->angle == 360)
	{
		this->angle = 0;
	}
	else if (this->angle == -90)
	{
		this->angle = 270;
	}
}