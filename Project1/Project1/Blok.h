#pragma once
#include <SFML/Graphics.hpp>
#ifndef Blok_h
#define Blok_h
class Blok
{
public:
	Blok();
	~Blok();
	int x, y;
	float angle;
	int width, height, hp;
	sf::Texture texture;
};
#endif
