#include "Pocisk.h"



Pocisk::Pocisk(int x, int y, int rot)
{
	this->texturel.loadFromFile("images/pociskl.png");
	this->textureu.loadFromFile("images/pocisku.png");
	this->texturer.loadFromFile("images/pociskr.png");
	this->textured.loadFromFile("images/pociskd.png");
	this->angle = rot;
	setRotation();
	sf::Vector2u pociskSize(texturel.getSize());
	this->width = pociskSize.x;
	this->height = pociskSize.y;
	this->x = x;
	this->y = y;
	setStartPosition();
	this->movement = 8;
}


Pocisk::~Pocisk()
{
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
bool Pocisk::sprawdzKolizjePociskPrzeszkoda()
{
	int mapa_przeszkody_size = GraDane::mapa.przeszkody.size();
	switch (angle)
	{
	case 90:
		if (y - movement < 0)
		{
			return true;
			break;
		}
		for (int i = 0; i <mapa_przeszkody_size; i++)
		{

			if (((x + width) > GraDane::mapa.przeszkody[i].x) &&
				(x < (GraDane::mapa.przeszkody[i].x + GraDane::mapa.przeszkody[i].width)) &&
				((y + height) > GraDane::mapa.przeszkody[i].y) &&
				(y < (GraDane::mapa.przeszkody[i].y + GraDane::mapa.przeszkody[i].height + movement)))
			{

				return true;
			}
		}
		break;
	case 270:
		if ((y + height + movement) > 900)
			return true;
		for (int i = 0; i <mapa_przeszkody_size; i++)
		{

			if (((x + width) > GraDane::mapa.przeszkody[i].x) &&
				(x < (GraDane::mapa.przeszkody[i].x + GraDane::mapa.przeszkody[i].width)) &&
				((y + height + movement) > GraDane::mapa.przeszkody[i].y) && //jak zmienimy pocisk.height na pocisk.width to si� zmienia bug tekstury...
				(y < (GraDane::mapa.przeszkody[i].y + GraDane::mapa.przeszkody[i].height)))
			{
				return true;

			}
		}
		break;
	case 0:
		if (x - movement < 0)
			return true;
		for (int i = 0; i <mapa_przeszkody_size; i++)
		{

			if (((x + height) > GraDane::mapa.przeszkody[i].x) &&
				(x < (GraDane::mapa.przeszkody[i].x + GraDane::mapa.przeszkody[i].width + movement)) &&
				((y + height) > GraDane::mapa.przeszkody[i].y) &&
				(y < (GraDane::mapa.przeszkody[i].y + GraDane::mapa.przeszkody[i].height)))
			{
				return true;
			}
		}
		break;
	case 180:
		if ((x + width + movement) > 1200)
			return true;
		for (int i = 0; i <mapa_przeszkody_size; i++)
		{

			if (((x + width + movement) > GraDane::mapa.przeszkody[i].x) &&
				(x < (GraDane::mapa.przeszkody[i].x + GraDane::mapa.przeszkody[i].width)) &&
				((y + height) > GraDane::mapa.przeszkody[i].y) &&
				(y < (GraDane::mapa.przeszkody[i].y + GraDane::mapa.przeszkody[i].height)))
			{

				return true;
			}
		}
		break;
	default:
		break;
	}
	return false;
}
