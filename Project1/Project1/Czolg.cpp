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
	Pocisk pocisk(x + width/2,y + height/2, angle);
	this->pociski.push_back(pocisk);
}

void Czolg::moveUp()
{
	if (this->angle != 90)
	{
		this->angle = 90;
		
	}
	else
		this->y -= 5;
}
void Czolg::moveDown()
{
	if (this->angle != 270)
	{
		this->angle = 270;
		
	}
	else
		this->y += 5;

}
void Czolg::moveRight()
{

	if (this->angle != 180)
	{
		this->angle = 180;
		
	}
	else
		this->x += 5;

}
void Czolg::moveLeft()
{
	if (this->angle != 0)
	{
		this->angle = 0;
		
	}
	else
		this->x -= 5;

}
