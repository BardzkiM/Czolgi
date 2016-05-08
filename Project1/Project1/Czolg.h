#pragma once
#include "Pocisk.h"
#include "Blok.h"
#include "SFML/Graphics.hpp"
#ifndef _CZOLG_H
#define _CZOLG_H
class Czolg : public Blok
{
public:
	Czolg();
	~Czolg();
	std::vector <Pocisk> pociski;
	void addPocisk();
	void setInitialPosition(int x, int y);
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
	

};

#endif