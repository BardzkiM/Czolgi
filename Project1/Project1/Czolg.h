#pragma once
#include "Pocisk.h"
#include "Blok.h"
#include "SFML/Graphics.hpp"
#ifndef Czolg_h
#define Czolg_h
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