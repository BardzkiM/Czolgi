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