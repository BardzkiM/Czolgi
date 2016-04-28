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
	sf::Texture texturel;
	sf::Texture textureu;
	sf::Texture texturer;
	sf::Texture textured;

	std::vector <Pocisk> pociski;
	void addPocisk();

};

#endif