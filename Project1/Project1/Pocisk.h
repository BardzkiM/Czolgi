#pragma once
#include "Blok.h"
#include <SFML\Graphics.hpp>
#ifndef Pocisk_h
#define Pocisk_h
class Pocisk : public Blok
{
public:
	Pocisk(int x, int y, int rot);
	~Pocisk();
	int id_czolgu;
	float speed;
	char type;
	sf::Texture texturel;
	sf::Texture textureu;
	sf::Texture textured;
	sf::Texture texturer;

};
#endif
