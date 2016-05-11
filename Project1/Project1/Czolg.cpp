#include "Czolg.h"
#include <iostream>
#include <math.h>
#define M_PI 3.14159265358979323846


std::string Czolg::serialize()
{
	std::ostringstream archive_ostream;
	std::string serialized_data_str;
	boost::archive::text_oarchive oarchive(archive_ostream);
	oarchive << this->x << this->y << this->angle << this->height << this->width << this->hp;
	serialized_data_str = archive_ostream.str();
	std::cout << "[TANK]serialized data: " << serialized_data_str << std::endl;
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

	if (!bufferTank.loadFromFile("sounds/tankMove.wav"))
	{
		std::cerr << "blad czytania dzwieku!" << std::endl;
		exit(-12);
	}

	if (!bufferBullet.loadFromFile("sounds/wystrzal.wav"))
	{
		std::cerr << "blad czytania dzwieku!" << std::endl;
		exit(-12);
	}



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

	Pocisk pocisk(x, y, this->angle);
	sound.setBuffer(bufferBullet);
	sound.play();

	this->pociski.push_back(pocisk);
	sound.play();
}
void Czolg::removePocisk(int j)
{
	if (this->pociski.size() > 1)
	{
		this->pociski[j] = this->pociski.back();
		this->pociski.pop_back();
	}
	else
		this->pociski.clear();

}
void Czolg::move(int x, int y)
{
	sound.setBuffer(bufferTank);

	//sound.play();
	this->y += y*movement;
	this->x += x*movement;
}
bool Czolg::sprawdzKolizjeCzolgPrzeszkoda()
{
	int mapa_przeszkody_size = GraDane::mapa.przeszkody.size();
	switch (angle)
	{
	case 90:
		if (y - movement < 0)
			return true;
		for (int i = 0; i <mapa_przeszkody_size; i++)
		{
			if (((x + GraDane::mapa.przeszkody[i].width) > GraDane::mapa.przeszkody[i].x) &&
				(x < (GraDane::mapa.przeszkody[i].x + GraDane::mapa.przeszkody[i].width)) &&
				((y + GraDane::mapa.przeszkody[i].height) > GraDane::mapa.przeszkody[i].y) &&
				(y < (GraDane::mapa.przeszkody[i].y + GraDane::mapa.przeszkody[i].height + movement)))
				return true;
		}
		break;
	case 270:
		if ((y + height + movement) > 900)
			return true;
		for (int i = 0; i <mapa_przeszkody_size; i++)
		{

			if (((x + GraDane::mapa.przeszkody[i].width) > GraDane::mapa.przeszkody[i].x) &&
				(x < (GraDane::mapa.przeszkody[i].x + GraDane::mapa.przeszkody[i].width)) &&
				((y + GraDane::mapa.przeszkody[i].height + movement) > GraDane::mapa.przeszkody[i].y) &&
				(y < (GraDane::mapa.przeszkody[i].y + GraDane::mapa.przeszkody[i].height)))
				return true;
		}
		break;
	case 0:
		if (x - movement < 0)
			return true;
		for (int i = 0; i <mapa_przeszkody_size; i++)
		{

			if (((x + GraDane::mapa.przeszkody[i].width) > GraDane::mapa.przeszkody[i].x) &&
				(x < (GraDane::mapa.przeszkody[i].x + GraDane::mapa.przeszkody[i].width + movement)) &&
				((y + GraDane::mapa.przeszkody[i].height) > GraDane::mapa.przeszkody[i].y) &&
				(y < (GraDane::mapa.przeszkody[i].y + GraDane::mapa.przeszkody[i].height)))
				return true;
		}
		break;
	case 180:
		if ((x + width + movement) > 1200)
			return true;
		for (int i = 0; i <mapa_przeszkody_size; i++)
		{

			if (((x + GraDane::mapa.przeszkody[i].width + movement) > GraDane::mapa.przeszkody[i].x) &&
				(x < (GraDane::mapa.przeszkody[i].x + GraDane::mapa.przeszkody[i].width)) &&
				((y + GraDane::mapa.przeszkody[i].height) > GraDane::mapa.przeszkody[i].y) &&
				(y < (GraDane::mapa.przeszkody[i].y + GraDane::mapa.przeszkody[i].height)))
				return true;
		}
		break;

	default:
		break;

	}
	return false;
}

void Czolg::sprawdzKolizjePociskowPrzeszkod()
{
	int p_size = pociski.size();

	for (int i = 0; i < p_size; i++)
	{
		if (pociski[i].sprawdzKolizjePociskPrzeszkoda())
		{
			
			removePocisk(i);
			i--; 
			p_size--;
		}
		else
		{
			switch (pociski[i].angle)
			{
			case 0:
				pociski[i].x -= pociski[i].movement;
				break;

			case 90:
				pociski[i].y -= pociski[i].movement;
				break;
			case 180:
				pociski[i].x += pociski[i].movement;
				break;
			case 270:
				pociski[i].y += pociski[i].movement;
				break;
			}
		}
	}

}