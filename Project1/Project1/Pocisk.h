#pragma once
#include "Blok.h"
#include <SFML\Graphics.hpp>
#ifndef _POCISK_H
#define _POCISK_H
class Pocisk : public Blok
{
public:
	Pocisk(int x, int y, int rot);
	~Pocisk();
	int id_czolgu;
	float speed;
	char type;
	void setTexture();

};
#endif
