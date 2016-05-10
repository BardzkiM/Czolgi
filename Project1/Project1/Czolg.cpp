#include "Czolg.h"
#include <iostream>
#include <math.h>
#define M_PI 3.14159265358979323846

std::string Czolg::serialize()
{
	std::ostringstream archive_ostream;
	std::string serialized_data_str;
	boost::archive::text_oarchive oarchive(archive_ostream);
	oarchive << this->x << this->y << this->angle << this->height<< this->width << this->hp;
	serialized_data_str = archive_ostream.str();
	std::cout << "serialized data: " << serialized_data_str << std::endl;		
	return serialized_data_str;
	
}

void Czolg::deserialize(std::string stream)
{
	std::istringstream archive_istream(stream);
	boost::archive::text_iarchive iarchive(archive_istream);
	iarchive >> this->x;
	iarchive >> this->y;
	iarchive >> this->angle;
	iarchive >> this->height;
	iarchive >> this->width;
	iarchive >> this->hp;
	std::cout << "Czolg zostal poprawnie zdeserializowany" << std::endl;
}


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
