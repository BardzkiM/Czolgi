#pragma once
#include <SFML/Graphics.hpp>
#ifndef _BLOK_H
#define _BLOK_H
class Blok
{
public:
	Blok();
	~Blok();

	int x, y;
	int angle;
	int width, height, hp;
	int movement;	
	sf::Texture texture;
	sf::Texture texturel;
	sf::Texture textureu;
	sf::Texture texturer;
	sf::Texture textured;

	void setRotation();
};
#endif
