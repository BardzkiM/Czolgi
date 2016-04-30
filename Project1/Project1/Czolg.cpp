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
	Pocisk pocisk(this->x, this->y, this->angle);
	this->pociski.push_back(pocisk);
}

void Czolg::move(int direction)
{
	this->x -= (int)(cos(angle*M_PI / 180) *5)*direction;
	this->y -= (int)(sin(angle*M_PI / 180) * 5)*direction;

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

	switch (this->angle)
	{
		case 0:
			texture = texturel;
			break;
		case 90:
			texture = textureu;
			break;
		case 180:
			texture = texturer;
			break;
		case 270:
			texture = textured;
			break;


	}
}