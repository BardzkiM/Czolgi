#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <math.h>


#ifndef _WYKONAWCY_H
#define _WYKONAWCY_H

class Wykonawcy
{
public:
	Wykonawcy();
	~Wykonawcy();
	
	int set_bg(sf::RenderWindow * window);
	sf::Text napisy(sf::Text text, std::string nazwa, float x, float y, bool style, int size);
	sf::Texture wykonawcy_bg;
	sf::Text wstep;
	sf::Text wykonawca1;
	sf::Text wykonawca2;
	sf::Text wykonawca3;
	sf::Text wykonawca4;
	sf::Text wykonawca5;
	
private:

};

#endif