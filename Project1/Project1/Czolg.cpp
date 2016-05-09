#include "Czolg.h"
#include <iostream>
#include <math.h>
#define M_PI 3.14159265358979323846

void Czolg::serialize()
{
	std::ostringstream archive_ostream;
	std::string serialized_data_str;
	boost::archive::text_oarchive oarchive(archive_ostream);
	oarchive << this->x << this->y << this->angle << this->height<< this->width << this->hp;
	serialized_data_str = archive_ostream.str();
	std::cout << "serialized data: " << serialized_data_str << std::endl;

	std::istringstream archive_istream(serialized_data_str);
	boost::archive::text_iarchive iarchive(archive_istream);
	iarchive >> this->x;
	iarchive >> this->y;
	iarchive >> this->angle;
	iarchive >> this->height;
	iarchive >> this->width;
	iarchive >> this->hp;

	/*cereal::BinaryOutputArchive oarchive(mystringstream);
	oarchive(this->x,this->y,this->angle,this->height,this->width,this->hp);*/
	
	
}

void Czolg::deserialize(std::stringstream stream)
{
	/*cereal::BinaryInputArchive iarchive(stream);
	iarchive(this->x, this->y, this->angle, this->height, this->width, this->hp);*/
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
	Pocisk pocisk(x + width/2,y + height/2, this->angle);
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
