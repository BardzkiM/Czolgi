#pragma once
#include "Pocisk.h"
#include "Blok.h"

#include <autoserial/autoserial.h>
#include <sstream>
#include "SFML/Graphics.hpp"
#ifndef _CZOLG_H
#define _CZOLG_H
class Czolg : public Blok
{
public:
	Czolg();
	~Czolg();
	int movement;
	std::vector <Pocisk> pociski;
	void addPocisk();
	void setInitialPosition(int x, int y);
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
	std::stringstream serialize();
	void deserialize(std::stringstream stream);
	
private:
	std::stringstream mystringstream;
};

#endif