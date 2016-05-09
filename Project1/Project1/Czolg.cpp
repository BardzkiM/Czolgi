#include "Czolg.h"
#include <iostream>
#include <math.h>
#define M_PI 3.14159265358979323846



Czolg::Czolg()
{
	this->texturel.loadFromFile("images/tankl.png");
	this->textureu.loadFromFile("images/tanku.png");
	this->texturer.loadFromFile("images/tankr.png");
	this->textured.loadFromFile("images/tankd.png");

	this->texture.loadFromFile("images/tankl.png");

	sf::Vector2u tankSize(texturel.getSize());
	this->width = tankSize.x;
	this->height = tankSize.y;
	this->movement = 5;
	 

}


Czolg::~Czolg()
{
}

void Czolg::setInitialPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Czolg::addPocisk()
{

	Pocisk pocisk(x ,y , this->angle);

	this->pociski.push_back(pocisk);
}

void Czolg::moveUp()
{
	if (this->angle != 90)
	{
		this->angle = 90;
		
	}
	else
		this->y -= this->movement;
}
void Czolg::moveDown()
{
	if (this->angle != 270)
	{
		this->angle = 270;
		
	}
	else
		this->y += this->movement;

}
void Czolg::moveRight()
{

	if (this->angle != 180)
	{
		this->angle = 180;
		
	}
	else
		this->x += this->movement;

}
void Czolg::moveLeft()
{
	if (this->angle != 0)
	{
		this->angle = 0;
		
	}
	else
		this->x -= this->movement;

}
