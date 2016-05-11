#pragma once
#include "Blok.h"
#include <SFML\Graphics.hpp>
#include "GraDane.h"
#ifndef _POCISK_H
#define _POCISK_H
class Pocisk : public Blok
{
public:
	Pocisk(int x, int y, int rot);
	~Pocisk();
	int id_czolgu;
	char type;
	void setTexture();
	void setStartPosition();
	bool sprawdzKolizjePociskPrzeszkoda();

};
#endif
