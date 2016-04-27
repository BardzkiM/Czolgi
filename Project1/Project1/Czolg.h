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
	sf::Texture texture;

private:
	Pocisk pociski[20];
	

};

#endif