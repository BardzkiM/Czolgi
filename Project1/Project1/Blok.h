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
	sf::Texture texture;
};
#endif
